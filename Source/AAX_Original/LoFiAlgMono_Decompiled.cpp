#include "LoFiAlgDefs.h"
#include <cmath>
#include <algorithm>

namespace ProLoFi {
namespace AAX_Original {

// ============================================================================
// Exact 1:1 C++ Decompilation of AlgEntry from:
//   - LoFiAlgMono.dll   (.text 0x0000..0x0f20, TI TMS320C67x+ VLIW)
//   - LoFiAlgStereo.dll (.text 0x0000..0x0fa0, TI TMS320C67x+ VLIW)
//
// Each invocation of AlgEntry processes a 4-sample AAX DSP sub-block per
// active plugin instance.
// ============================================================================

static void ProcessChannelBlock4(
    const float* __restrict inBuf,          // *+A3[0..3]  (4 input samples)
    float* __restrict       outBuf,         // *+B16[0..3] (4 output samples)
    int32_t                 bypass,         // *+B15[42]
    int32_t                 quantType,      // A30 (0 = Linear, 1 = Adaptive)
    const LoFiSRFilterCoeffs& srCoeffs,     // *+A5[5]
    const LoFiQuantCoeffs&  quantCoeffs,    // *+A5[6]
    const LoFiNoiseCoeffs&  noiseCoeffs,    // *+A5[7]
    const LoFiDistCoeffs&   distCoeffs,     // *+A5[8]
    const LoFiSatCoeffs&    satCoeffs,      // *+A5[9]
    LoFiState&              state,          // *+A5[10] (A31)
    const float* __restrict waveTable,      // *+A5[11] (A11, 65 floats)
    float* __restrict       envHistory,     // *+A5[12] (A12, 64 floats)
    float&                  inPeakMeter,    // **+A15[1] (A17)
    float&                  outPeakMeter)   // **+A15[0] (A18)
{
    // ------------------------------------------------------------------------
    // [0x00b4..0x0420] Stage 1A: Sample-Rate Decimation (Sample & Hold)
    // ------------------------------------------------------------------------
    float decimated[4]; // *+B15[32..35]
    const int32_t decimationStep = srCoeffs.decimationStep; // B29 (*+B15[39])
    int32_t holdCounter = state.srHoldCounter;              // B3  (*+A31[3])
    int32_t subCounter  = state.srSubCounter;               // B31 (*+A31[5] / *+B15[40])
    float   heldSample  = state.heldSample;                 // *+A31[9]

    for (int i = 0; i < 4; ++i) {
        // [0x00b4..0x0144] Check if decimationStep > 2 and holdCounter > 2
        bool triggerSample = false;
        if (decimationStep <= 1) {
            triggerSample = true;
            holdCounter = 1;
            subCounter = 1;
        } else {
            if (holdCounter > 2 && decimationStep > 2) {
                triggerSample = false;
            } else if (subCounter == 1) {
                triggerSample = true;
            }

            if (holdCounter < decimationStep) {
                holdCounter += 1;
            } else {
                holdCounter = 1;
                triggerSample = true;
            }
        }

        if (triggerSample) {
            heldSample = inBuf[i]; // [0x0118, 0x01ac, 0x02f8, 0x03e4] STW in[i], *+A31[9]
        }
        decimated[i] = heldSample; // [0x01e4, 0x01bc, 0x01f4, 0x0410] *+B15[32..35]
    }

    state.srHoldCounter = holdCounter; // [0x05fc] STW B18, *+A31[3]
    state.srSubCounter  = subCounter;  // [0x0654] STW B23, *+A31[5]
    state.heldSample    = heldSample;  // [0x03e4] STW A5,  *+A31[9]

    // ------------------------------------------------------------------------
    // [0x01e8..0x0684] Stage 1B: 4th-Order (2-Stage Biquad) Anti-Aliasing Filter
    // ------------------------------------------------------------------------
    double filtered[4]; // *+B15[16..23] (4 doubles at B15 + 64 bytes)

    if (srCoeffs.filterEnable != 0) {
        // [0x0210..0x0640] Cascaded double-precision biquad evaluation
        // Note: Coefficients in LoFiSRFilterCoeffs are pre-scaled by 0.5 in
        // LoFi_EffectParameters, and the DSP doubles the accumulator via ADDDP X, X, X
        // ([0x02f0, 0x03b8, 0x03bc, 0x0454, 0x046c, 0x04d8, 0x04f8, 0x0524, 0x0560, 0x0598, 0x05f4, 0x061c]).
        double x1 = state.biquad1_x1;
        double x2 = state.biquad1_x2;
        double y1 = state.biquad1_y1;
        double y2 = state.biquad1_y2;
        double z1 = state.biquad2_y1;
        double z2 = state.biquad2_y2;

        for (int i = 0; i < 4; ++i) {
            const double x0 = static_cast<double>(decimated[i]);

            // Stage 1 Biquad:
            double w = srCoeffs.b0_stage1 * x0
                     + srCoeffs.b1_stage1 * x1
                     + srCoeffs.b2_stage1 * x2
                     - srCoeffs.a1_stage1 * y1
                     - srCoeffs.a2_stage1 * y2;
            w = w + w; // [0x02f0 / 0x03b8] ADDDP (compensates for 0.5 coefficient scaling)

            x2 = x1;
            x1 = x0;
            y2 = y1;
            y1 = w;

            // Stage 2 Biquad:
            // Numerator uses (1, 2, 1) * b_stage2 = b_stage2 * (w + 2*y2_prev + ...)
            double u = srCoeffs.b_stage2 * (w + 2.0 * y2 + x2)
                     - srCoeffs.a1_stage2 * z1
                     - srCoeffs.a2_stage2 * z2;
            u = u + u; // [0x0454 / 0x0598 / 0x05f4] ADDDP

            z2 = z1;
            z1 = u;

            filtered[i] = u; // [0x0590..0x067c] STW *+B15[16..23]
        }

        state.biquad1_x1 = x1;
        state.biquad1_x2 = x2;
        state.biquad1_y1 = y1;
        state.biquad1_y2 = y2;
        state.biquad2_y1 = z1;
        state.biquad2_y2 = z2;
    } else {
        // [0x0584, 0x0614, 0x0648, 0x0660] [!A1] Bypass anti-aliasing filter
        filtered[0] = static_cast<double>(decimated[0]);
        filtered[1] = static_cast<double>(decimated[1]);
        filtered[2] = static_cast<double>(decimated[2]);
        filtered[3] = static_cast<double>(decimated[3]);
    }

    // ------------------------------------------------------------------------
    // [0x0690..0x08b0] Stage 2 ($C$L2 loop, B2 = 4 iterations):
    //   - 64-Sample Sliding-Window Envelope Detector (runningAbsSum)
    //   - Data-Driven 24-Bit Shift Register Noise Generator & Envelope Modulation
    //   - Linear vs. Adaptive Bit-Depth Quantization
    // ------------------------------------------------------------------------
    double   runningAbsSum = state.runningAbsSum; // A7:A6 (*+A31[20..21])
    int32_t  envIdx        = state.envHistoryIdx; // A3    (*+A31[0])
    uint32_t lfsrState     = state.lfsrState;     // B26   (*+A31[7])
    const int32_t maxEnvIdx = srCoeffs.envWindowMaxIdx; // B21 (*+B26[18], typically 63)

    bool  signBits[4];   // *+B15[7..10] (*B17++[1])
    float workSamples[4]; // *+B15[32..35] (*++A21[1])

    // [0x083c..0x086c] Local copy of $P$T0$1 = {1.0f, 0.5f, 0.25f, 0.125f, 0.0625f, 0.03125f}
    const float* adaptiveTable = kAdaptiveQuantScaleTable;

    for (int i = 0; i < 4; ++i) {
        // 1. Update 64-sample sliding window sum of |inBuf[i]|
        // [0x06f0..0x0714] runningAbsSum = runningAbsSum - envHistory[envIdx] + fabsf(inBuf[i])
        const float oldestAbs = envHistory[envIdx];
        const float currentAbs = std::fabs(inBuf[i]); // [0x0708] ABSSP B4, B24
        runningAbsSum = (runningAbsSum - static_cast<double>(oldestAbs))
                      + static_cast<double>(currentAbs);
        if (runningAbsSum < 0.0) {
            runningAbsSum = 0.0;
        }

        // [0x07a4..0x07a8, 0x0878..0x0880] Store new |inBuf[i]| and wrap circular index
        envHistory[envIdx] = currentAbs;
        envIdx += 1;
        if (envIdx > maxEnvIdx) {
            envIdx = 0; // [0x0880] [!B1] ZERO A3
        }

        // 2. Data-driven 24-bit shift register noise generator
        // [0x06fc..0x0780] Extracts bit 8 (0x100) of (int)(filtered[i] * 2^24)
        // and shifts it into bit 23 (sign-extended to 32 bits) of lfsrState (B26).
        double sampleD = filtered[i];
        const int32_t fixed24 = static_cast<int32_t>(sampleD * 16777216.0); // [0x0704..0x073c] * 0x41600000_00000000
        const int32_t bit8 = fixed24 & 0x100;                               // [0x0744..0x074c] AND 256, B8, B1
        const uint32_t shiftedLfsr = (lfsrState & 0x00FFFFFFu) >> 1;        // [0x0750] EXTU B26, 8, 9, B8
        const int32_t msbMask = (bit8 != 0) ? static_cast<int32_t>(0xFF800000u) : 0; // [0x0754..0x075c] SHL -1, 23
        const int32_t signedLfsr = msbMask | static_cast<int32_t>(shiftedLfsr);      // [0x0764] OR A5, B8, A5
        lfsrState = static_cast<uint32_t>(signedLfsr);                      // [0x077c] B26 = A5

        // [0x0718..0x07ec] If Noise is enabled ([B0]), modulate noise by sliding envelope and add to sampleD
        if (noiseCoeffs.enable != 0) {
            // 0x3f700000_00000000 = 2^-8 = 1.0 / 256.0
            const double envNorm = runningAbsSum * (1.0 / 256.0);           // [0x071c, 0x0738]
            const double envScaled = noiseCoeffs.envModGain * envNorm;      // [0x0760]
            // 0x3e800000_00000000 = 2^-23
            const double noiseVal = (static_cast<double>(signedLfsr) * envScaled) * 1.1920928955078125e-07; // [0x0768..0x07ac]
            sampleD += noiseVal;                                            // [0x07ec] ADDDP
        }

        // 3. Adaptive vs. Linear Bit-Depth Quantization
        // [0x0734, 0x076c, 0x07b4..0x07f0] Compute adaptive exponent B19 in {0..5}
        int32_t adaptiveExp = 0; // B19
        if (quantType != 0) {
            // [!A2] Adaptive quantization mode:
            const uint32_t v = static_cast<uint32_t>(static_cast<int32_t>(runningAbsSum)) >> 3; // [0x07b4] SHRU A24, 3, A22
            adaptiveExp = static_cast<int32_t>(v == 0)
                        + static_cast<int32_t>((v >> 1) == 0)
                        + static_cast<int32_t>((v >> 2) == 0)
                        + static_cast<int32_t>((v >> 3) == 0)
                        + static_cast<int32_t>((v >> 4) == 0); // [0x07b8..0x07e8] -> 0..5
        }

        // [0x081c..0x0834] Extract sign bit (sampleD < 0.0) and take magnitude |sampleD|
        const bool isNegative = (sampleD < 0.0); // [0x081c] CMPGTDP 0.0, A9:A8, B1
        signBits[i] = isNegative;                // [0x082c] STW B1, *B17++[1]
        const double absSampleD = isNegative ? -sampleD : sampleD; // [0x0820..0x0824] XOR sign bit

        // [0x0874, 0x0894] Default unquantized magnitude
        workSamples[i] = static_cast<float>(absSampleD);

        // [0x07f0..0x08b0] Quantize magnitude if Sample Size < 24 bits ([A1] where A1 = quantCoeffs.enable)
        if (quantCoeffs.enable != 0) {
            const double upScale = quantCoeffs.scale * static_cast<double>(1 << adaptiveExp); // [0x07f0..0x0804]
            const double downScale = static_cast<double>(adaptiveTable[adaptiveExp]) * quantCoeffs.invScale; // [0x0870, 0x0884]
            const int32_t qInt = static_cast<int32_t>(absSampleD * upScale + 0.5); // [0x0830, 0x0860, 0x087c] DPTRUNC
            const double qMag = static_cast<double>(qInt) * downScale;             // [0x088c, 0x089c] INTDP + MPYDP
            workSamples[i] = static_cast<float>(qMag);                             // [0x08a8, 0x08b0] DPSP + STW
        }
    }

    // [0x09c8..0x09dc] Persist envelope detector & LFSR state
    state.envHistoryIdx = envIdx;
    state.lfsrState     = lfsrState;
    state.runningAbsSum = runningAbsSum;

    // ------------------------------------------------------------------------
    // [0x08b4..0x0cdc] Stage 3: 65-Point Lookup Table Waveshaping Distortion
    //   - Operates on non-negative magnitudes workSamples[0..3]
    //   - Restores signBits[0..3] afterward ([0x09e4..0x0cdc])
    // ------------------------------------------------------------------------
    for (int i = 0; i < 4; ++i) {
        float mag = workSamples[i];

        if (distCoeffs.enable != 0) {
            // [0x08cc..0x08ec] Scale magnitude by drive and clamp to 64.0f (*+B15[36] = 0x42800000)
            float scaledIdx = mag * distCoeffs.drive;
            if (static_cast<double>(scaledIdx) > 64.0) {
                scaledIdx = 64.0f; // [0x08e4..0x08ec]
            }

            // [0x0900..0x0988] Split into integer index (0..64) and fractional part
            int32_t idx = static_cast<int32_t>(scaledIdx);
            if (idx < 0)  idx = 0;
            if (idx > 63) idx = 63;
            const double frac = static_cast<double>(scaledIdx - static_cast<float>(idx));

            // Linearly interpolate waveTable[idx] and waveTable[idx + 1] in double precision
            const double t0 = static_cast<double>(waveTable[idx]);
            const double t1 = static_cast<double>(waveTable[idx + 1]);
            const float shaped = static_cast<float>((1.0 - frac) * t0 + frac * t1); // [0x093c..0x0988]

            // [0x0918, 0x0990, 0x09a8, 0x09b8] Blend dry and wet
            mag = mag * distCoeffs.dryMix + shaped * distCoeffs.wetMix;
        }

        // [0x09e4..0x0a08, 0x0ae8..0x0b14, 0x0bd4..0x0c00, 0x0cbc..0x0cdc]
        // Restore original sign bit from signBits[i]
        workSamples[i] = signBits[i] ? -mag : mag;
    }

    // ------------------------------------------------------------------------
    // [0x0a30..0x0e2c] Stage 4: Soft-Knee Slew / Saturation Stage ([B0])
    //   - Uses persistent state.prevSatState (s_{n-1} at *+A31[18..19])
    //   - Applies soft-knee compression to sample-to-sample difference (or signal)
    //     with threshold T = satCoeffs.threshold, kneeSlope k = satCoeffs.kneeSlope,
    //     and post-gain = satCoeffs.postGain.
    // ------------------------------------------------------------------------
    double prevSat = state.prevSatState; // [0x09e8] LDDW *+A31[18], A23:A22

    if (satCoeffs.enable != 0) {
        const double T = satCoeffs.threshold; // *+B27[0]
        const double k = satCoeffs.kneeSlope; // *+B30[1]
        const double postGain = satCoeffs.postGain; // *+B4[2]

        float satPreGain[4];
        for (int i = 0; i < 4; ++i) {
            const double x = static_cast<double>(workSamples[i]);
            const double diff = x - prevSat; // [0x0a3c, 0x0b48, 0x0c3c, 0x0d04] SUBDP

            double delta;
            if (diff > -T && diff < T) {
                // [0x0a78..0x0aac, 0x0b80..0x0bac, 0x0c74..0x0c90, 0x0d28..0x0d40]
                // Inside linear region |diff| < T: slope = 1.0, offset = 0.0
                delta = diff;
            } else {
                // Outside linear region |diff| >= T:
                const double signedT = (diff < 0.0) ? -T : T;
                delta = signedT + (diff - signedT) * k; // [0x0d34, 0x0d50, 0x0d68]
            }

            const float s_i = static_cast<float>(prevSat + delta); // [0x0b0c..0x0b28, etc.]
            satPreGain[i] = s_i;
            prevSat = static_cast<double>(s_i);
        }

        // [0x0df4, 0x0e08, 0x0e18] Save pre-postGain state of sample 3 into state.prevSatState
        state.prevSatState = static_cast<double>(satPreGain[3]);

        // [0x0d00, 0x0d88, 0x0dc0, 0x0dd0] Multiply by satCoeffs.postGain
        for (int i = 0; i < 4; ++i) {
            workSamples[i] = static_cast<float>(static_cast<double>(satPreGain[i]) * postGain);
        }
    } else {
        // [0x0df4, 0x0e08, 0x0e18] Even when saturation is disabled, state.prevSatState
        // tracks the last sample (A5 = workSamples[3]).
        state.prevSatState = static_cast<double>(workSamples[3]);
    }

    // ------------------------------------------------------------------------
    // [0x0d48..0x0e34] Stage 5: Master Bypass Wet/Dry Mix
    // ------------------------------------------------------------------------
    const float wetGain = (bypass == 0) ? 1.0f : 0.0f; // [0x0d48, 0x0d5c] B19
    const float dryGain = (bypass != 0) ? 1.0f : 0.0f; // [0x0da0]         B17

    for (int i = 0; i < 4; ++i) {
        outBuf[i] = workSamples[i] * wetGain + inBuf[i] * dryGain; // [0x0db0..0x0e34]
    }

    // ------------------------------------------------------------------------
    // [0x0e38..0x0ee4] Stage 6: Input & Output Peak Metering
    // ------------------------------------------------------------------------
    float inPeak  = inPeakMeter;  // *+A17[0]
    float outPeak = outPeakMeter; // *+A18[0]
    for (int i = 0; i < 4; ++i) {
        const float absIn  = std::fabs(inBuf[i]);  // [0x0e50, 0x0e70, 0x0e80, 0x0e9c] ABSSP
        const float absOut = std::fabs(outBuf[i]); // [0x0e88, 0x0ea4, 0x0ec0, 0x0ed4] ABSSP
        if (absIn > inPeak)   inPeak  = absIn;     // [0x0e5c..0x0eac] CMPGTSP
        if (absOut > outPeak) outPeak = absOut;    // [0x0e90..0x0edc] CMPGTSP
    }
    inPeakMeter  = inPeak;  // [0x0ec4] STW A5, *+A17[0]
    outPeakMeter = outPeak; // [0x0ee4] STW A8, *+A18[0]
}

// ============================================================================
// Mono Entry Point (LoFiAlgMono.dll @ 0x0000..0x0f20)
// ============================================================================
void AlgEntry_Mono(LoFiAlgContext* const* instanceListBegin,
                   LoFiAlgContext* const* instanceListEnd)
{
    for (auto it = instanceListBegin; it != instanceListEnd; ++it) {
        LoFiAlgContext* ctx = *it;
        ProcessChannelBlock4(
            ctx->inputChannels[0],
            ctx->outputChannels[0],
            *(ctx->bypass),
            *(ctx->quantType),
            *(ctx->srFilterCoeffs),
            *(ctx->quantCoeffs),
            *(ctx->noiseCoeffs),
            *(ctx->distCoeffs),
            *(ctx->satCoeffs),
            ctx->state[0],
            ctx->waveTable,
            ctx->envHistoryBuf,
            *(ctx->meterTapBuffers[1]), // Input Peak Meter  (*+A15[1])
            *(ctx->meterTapBuffers[0])  // Output Peak Meter (*+A15[0])
        );
    }
}

// ============================================================================
// Stereo Entry Point (LoFiAlgStereo.dll @ 0x0000..0x0fa0)
// Runs the identical channel processing loop for Left (ch=0) and Right (ch=1)
// ============================================================================
void AlgEntry_Stereo(LoFiAlgContext* const* instanceListBegin,
                     LoFiAlgContext* const* instanceListEnd)
{
    for (auto it = instanceListBegin; it != instanceListEnd; ++it) {
        LoFiAlgContext* ctx = *it;
        for (int ch = 0; ch < 2; ++ch) {
            ProcessChannelBlock4(
                ctx->inputChannels[ch],
                ctx->outputChannels[ch],
                *(ctx->bypass),
                *(ctx->quantType),
                *(ctx->srFilterCoeffs),
                *(ctx->quantCoeffs),
                *(ctx->noiseCoeffs),
                *(ctx->distCoeffs),
                *(ctx->satCoeffs),
                ctx->state[ch],
                ctx->waveTable,
                ctx->envHistoryBuf + (ch * 64),
                *(ctx->meterTapBuffers[2 + ch]), // Input L/R Peak Meters
                *(ctx->meterTapBuffers[0 + ch])  // Output L/R Peak Meters
            );
        }
    }
}

} // namespace AAX_Original
} // namespace ProLoFi
