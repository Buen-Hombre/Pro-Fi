#include "LoFi_EffectParameters.h"
#include <cmath>
#include <cstdio>
#include <algorithm>

namespace ProLoFi {
namespace AAX_Original {

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

LoFi_EffectParameters::LoFi_EffectParameters() {
    buildWaveTable();
}

void LoFi_EffectParameters::setHostSampleRate(double hostSr) {
    mHostSampleRate = (hostSr > 0.0) ? hostSr : 48000.0;
}

void LoFi_EffectParameters::setBypass(bool bypassed) {
    mBypass = bypassed;
}

void LoFi_EffectParameters::setSampleRateNorm(double norm01) {
    mSampleRateNorm = std::clamp(norm01, 0.0, 1.0);
}

void LoFi_EffectParameters::setAntiAliasPct(double pct0_100) {
    mAntiAliasPct = std::clamp(pct0_100, 0.0, 100.0);
}

void LoFi_EffectParameters::setSampleSizeBits(int bits2_24) {
    mSampleSizeBits = std::clamp(bits2_24, 2, 24);
}

void LoFi_EffectParameters::setQuantizationMode(int mode0_1) {
    mQuantMode = (mode0_1 != 0) ? 1 : 0;
}

void LoFi_EffectParameters::setNoisePct(double pct0_100) {
    mNoisePct = std::clamp(pct0_100, 0.0, 100.0);
}

void LoFi_EffectParameters::setDistortion(double dist0_10) {
    mDistortion = std::clamp(dist0_10, 0.0, 10.0);
}

void LoFi_EffectParameters::setSaturation(double sat0_10) {
    mSaturation = std::clamp(sat0_10, 0.0, 10.0);
}

// ============================================================================
// Sample Rate Decimation Divisor (63 steps, __const @ 0x124748 = 63.0)
// Maps normalized slider [0.0..1.0] -> step 0..63 -> integer divisor 64..1
// ============================================================================
int LoFi_EffectParameters::getDecimationStep() const {
    const int step = static_cast<int>(std::round(mSampleRateNorm * 63.0));
    const int divisor = 64 - std::clamp(step, 0, 63);
    return std::max(1, divisor);
}

double LoFi_EffectParameters::getEffectiveSampleRateHz() const {
    // Base rate normalized to 44.1 / 48 kHz family in Pro Tools Lo-Fi
    return mHostSampleRate / static_cast<double>(getDecimationStep());
}

// Reconstructed from LoFi_SRDisplayDelegateDecorator<double, 100, 2, 0>
// and string literals " Hz" (0x12f0ef), "bits" (0x12f18a), "%" (0x12f11a)
std::string LoFi_EffectParameters::formatSampleRateDisplay() const {
    char buf[32];
    const double hz = std::round(getEffectiveSampleRateHz() / 100.0) * 100.0;
    std::snprintf(buf, sizeof(buf), "%.0f Hz", hz);
    return std::string(buf);
}

std::string LoFi_EffectParameters::formatAntiAliasDisplay() const {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.0f%%", std::round(mAntiAliasPct));
    return std::string(buf);
}

std::string LoFi_EffectParameters::formatSampleSizeDisplay() const {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%d bits", mSampleSizeBits);
    return std::string(buf);
}

std::string LoFi_EffectParameters::formatQuantizationDisplay() const {
    return (mQuantMode == 0) ? "Linear" : "Adaptive";
}

std::string LoFi_EffectParameters::formatNoiseDisplay() const {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.1f%%", mNoisePct);
    return std::string(buf);
}

std::string LoFi_EffectParameters::formatDistortionDisplay() const {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.1f", mDistortion);
    return std::string(buf);
}

std::string LoFi_EffectParameters::formatSaturationDisplay() const {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%.1f", mSaturation);
    return std::string(buf);
}

// ============================================================================
// Exact piecewise linear dB meter taper from Contents/Resources/Taper.xml
// ============================================================================
float LoFi_EffectParameters::linearPeakToMeterPixels(float peakAmplitude) {
    if (peakAmplitude <= 1.58489319e-5f) { // <= -96 dB
        return 0.0f;
    }
    const float db = 20.0f * std::log10(peakAmplitude);
    struct BreakPoint { float db; float px; };
    static constexpr BreakPoint kTaper[] = {
        { -96.0f,   0.0f },
        { -48.0f,  17.0f },
        { -24.0f,  42.0f },
        { -18.0f,  61.0f },
        { -12.0f,  84.0f },
        {  -6.0f, 123.0f },
        {  -3.0f, 146.0f },
        {  -2.0f, 164.0f },
        {  -1.0f, 181.0f },
        {   0.0f, 197.0f }
    };
    if (db >= 0.0f) return 197.0f;
    for (int i = 0; i < 9; ++i) {
        if (db >= kTaper[i].db && db <= kTaper[i + 1].db) {
            const float t = (db - kTaper[i].db) / (kTaper[i + 1].db - kTaper[i].db);
            return kTaper[i].px + t * (kTaper[i + 1].px - kTaper[i].px);
        }
    }
    return 0.0f;
}

// ============================================================================
// 65-entry Waveshaper Distortion Lookup Table (*+A5[11])
// Indexed in AlgEntry [0x08cc..0x0988] over u * drive in [0.0 .. 64.0]
// ============================================================================
void LoFi_EffectParameters::buildWaveTable() {
    for (int i = 0; i <= 64; ++i) {
        const double x = static_cast<double>(i) / 64.0;
        // Soft-to-hard saturation curve normalized so table[0] = 0.0 and table[64] = 1.0
        mWaveTable[i] = static_cast<float>(std::tanh(3.5 * x) / std::tanh(3.5));
    }
}

// ============================================================================
// Coefficient Generator populating *+A5[5..9] for AlgEntry
// ============================================================================
void LoFi_EffectParameters::updateCoefficients(
    LoFiSRFilterCoeffs& srOut,
    LoFiQuantCoeffs&    quantOut,
    LoFiNoiseCoeffs&    noiseOut,
    LoFiDistCoeffs&     distOut,
    LoFiSatCoeffs&      satOut) const
{
    // 1. Sample Rate & 4th-Order Cascaded Butterworth Lowpass Anti-Aliasing Filter (*+A5[5])
    const int decStep = getDecimationStep();
    srOut.decimationStep  = decStep;
    srOut.envWindowMaxIdx = 63; // 64-sample sliding window (indices 0..63)
    srOut.padding         = 0;

    // Anti-Alias filter is enabled when Sample Rate is reduced (< max) and Anti-Alias > 0%
    if (decStep > 1 && mAntiAliasPct > 0.0) {
        srOut.filterEnable = 1;
        // Effective Nyquist of the decimated rate, shifted by Anti-Alias % (100% = full anti-aliasing)
        const double nyquistRatio = 1.0 / static_cast<double>(decStep);
        // As Anti-Alias goes from 100% down to 0%, cutoff opens up toward host Nyquist
        const double aaNorm = mAntiAliasPct / 100.0;
        const double fcNorm = std::clamp(
            nyquistRatio * (0.45 * aaNorm + 1.8 * (1.0 - aaNorm)),
            0.005, 0.49
        );

        const double omega = M_PI * fcNorm;
        const double K     = std::tan(omega);
        const double K2    = K * K;

        // 4th-order Butterworth Q values: Q1 = 0.54119610, Q2 = 1.30656296
        const double Q1    = 0.541196100146197;
        const double Q2    = 1.3065629648763766;

        const double norm1 = 1.0 / (1.0 + K / Q1 + K2);
        const double b0_1  = K2 * norm1;
        const double b1_1  = 2.0 * b0_1;
        const double b2_1  = b0_1;
        const double a1_1  = 2.0 * (K2 - 1.0) * norm1;
        const double a2_1  = (1.0 - K / Q1 + K2) * norm1;

        const double norm2 = 1.0 / (1.0 + K / Q2 + K2);
        const double b0_2  = K2 * norm2;
        const double a1_2  = 2.0 * (K2 - 1.0) * norm2;
        const double a2_2  = (1.0 - K / Q2 + K2) * norm2;

        // Pre-scale by 0.5 because AlgEntry doubles the accumulator via ADDDP X, X, X
        srOut.b0_stage1 = 0.5 * b0_1;
        srOut.b1_stage1 = 0.5 * b1_1;
        srOut.b2_stage1 = 0.5 * b2_1;
        srOut.a1_stage1 = 0.5 * a1_1;
        srOut.a2_stage1 = 0.5 * a2_1;

        srOut.b_stage2  = 0.5 * b0_2;
        srOut.a1_stage2 = 0.5 * a1_2;
        srOut.a2_stage2 = 0.5 * a2_2;
    } else {
        srOut.filterEnable = 0;
        srOut.b0_stage1 = 0.5;
        srOut.b1_stage1 = 0.0;
        srOut.b2_stage1 = 0.0;
        srOut.a1_stage1 = 0.0;
        srOut.a2_stage1 = 0.0;
        srOut.b_stage2  = 0.5;
        srOut.a1_stage2 = 0.0;
        srOut.a2_stage2 = 0.0;
    }

    // 2. Sample Size / Bit-Depth Quantization (*+A5[6])
    // Range: 2..24 bits (__const @ 0x124708 = {2, 24})
    quantOut.pad0 = 0;
    if (mSampleSizeBits < 24) {
        quantOut.enable   = 1;
        const double steps = std::ldexp(1.0, mSampleSizeBits - 1); // 2^(bits - 1)
        quantOut.scale    = steps;
        quantOut.invScale = 1.0 / steps;
    } else {
        quantOut.enable   = 0;
        quantOut.scale    = 8388608.0; // 2^23
        quantOut.invScale = 1.0 / 8388608.0;
    }

    // 3. Envelope-Modulated 24-Bit Shift Register Noise (*+A5[7])
    noiseOut.pad0 = 0;
    if (mNoisePct > 0.0) {
        noiseOut.enable     = 1;
        // Scales 64-sample runningAbsSum/256 envelope; * 4.0 normalizes 64/256 = 0.25 window gain
        noiseOut.envModGain = (mNoisePct / 100.0) * 4.0;
    } else {
        noiseOut.enable     = 0;
        noiseOut.envModGain = 0.0;
    }

    // 4. Waveshaping Distortion (*+A5[8])
    if (mDistortion > 0.0) {
        distOut.enable = 1;
        const double dNorm = mDistortion / 10.0;
        // Maps [0..1] magnitude into [0..64] lookup table index with increasing drive
        distOut.drive  = static_cast<float>(64.0 * (1.0 + 7.0 * dNorm));
        distOut.wetMix = static_cast<float>(std::min(1.0, dNorm * 1.25));
        distOut.dryMix = static_cast<float>(std::max(0.0, 1.0 - dNorm));
    } else {
        distOut.enable = 0;
        distOut.drive  = 64.0f;
        distOut.wetMix = 0.0f;
        distOut.dryMix = 1.0f;
    }

    // 5. Soft-Knee Slew / Saturation (*+A5[9])
    // Uses constant 11.0 from __const @ 0x124738: threshold = (11.0 - sat) / 11.0
    satOut.pad0 = 0;
    if (mSaturation > 0.0) {
        satOut.enable    = 1;
        const double sNorm = mSaturation / 10.0;
        satOut.threshold = std::max(0.02, (11.0 - mSaturation) / 11.0 * 0.5);
        satOut.kneeSlope = 1.0 / (1.0 + mSaturation * 1.5);
        satOut.postGain  = 1.0 / (satOut.threshold + (1.0 - satOut.threshold) * satOut.kneeSlope)
                         * (1.0 - 0.15 * sNorm);
    } else {
        satOut.enable    = 0;
        satOut.threshold = 1.0;
        satOut.kneeSlope = 1.0;
        satOut.postGain  = 1.0;
    }
}

} // namespace AAX_Original
} // namespace ProLoFi
