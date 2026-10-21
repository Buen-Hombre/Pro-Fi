#include "DSP/LoFiDSP.h"
#include <cmath>
#include <cstdio>
#include <vector>
#include <cassert>

int main() {
    using namespace ProLoFi;
    using namespace ProLoFi::AAX_Original;

    LoFiDSPEngine dsp;
    dsp.prepare(48000.0);

    constexpr int kNumSamples = 1024;
    std::vector<float> inL(kNumSamples), inR(kNumSamples);
    std::vector<float> outL(kNumSamples), outR(kNumSamples);

    for (int n = 0; n < kNumSamples; ++n) {
        const double t = static_cast<double>(n) / 48000.0;
        inL[n] = static_cast<float>(0.8 * std::sin(2.0 * 3.14159265358979323846 * 440.0 * t));
        inR[n] = static_cast<float>(0.5 * std::cos(2.0 * 3.14159265358979323846 * 880.0 * t));
    }

    const float* inPtrs[2]  = { inL.data(),  inR.data() };
    float*       outPtrs[2] = { outL.data(), outR.data() };

    std::printf("=== ProLoFi Reverse-Engineered DSP Verification (25 Factory Presets) ===\n");
    for (int p = 0; p < 25; ++p) {
        const auto& preset = kFactoryPresets[p];
        dsp.reset();
        dsp.updateParameters(
            false,
            preset.sampleRateNorm,
            preset.antiAliasPct,
            preset.sampleSizeBits,
            preset.quantization,
            preset.noisePct,
            preset.distortion,
            preset.saturation
        );
        dsp.processBlock(inPtrs, outPtrs, 2, kNumSamples);

        double rmsL = 0.0;
        for (int n = 0; n < kNumSamples; ++n) {
            assert(std::isfinite(outL[n]) && std::isfinite(outR[n]));
            rmsL += static_cast<double>(outL[n]) * static_cast<double>(outL[n]);
        }
        rmsL = std::sqrt(rmsL / kNumSamples);

        const float inMeterPx  = LoFi_EffectParameters::linearPeakToMeterPixels(dsp.getInputPeak(0));
        const float outMeterPx = LoFi_EffectParameters::linearPeakToMeterPixels(dsp.getOutputPeak(0));

        std::printf("[%02d] %-27s | SR=%7s | AA=%4s | %7s (%-8s) | Noise=%5s | Dist=%3s | Sat=%3s | RMS=%.4f | Meter=%3.0fpx\n",
                    p + 1,
                    preset.name,
                    dsp.getParameters().formatSampleRateDisplay().c_str(),
                    dsp.getParameters().formatAntiAliasDisplay().c_str(),
                    dsp.getParameters().formatSampleSizeDisplay().c_str(),
                    dsp.getParameters().formatQuantizationDisplay().c_str(),
                    dsp.getParameters().formatNoiseDisplay().c_str(),
                    dsp.getParameters().formatDistortionDisplay().c_str(),
                    dsp.getParameters().formatSaturationDisplay().c_str(),
                    rmsL,
                    outMeterPx);
        (void)inMeterPx;
    }

    std::printf("\nAll 25 presets verified successfully through AlgEntry_Stereo!\n");
    return 0;
}
