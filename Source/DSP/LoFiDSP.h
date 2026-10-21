#pragma once

#include "../AAX_Original/LoFiAlgDefs.h"
#include "../AAX_Original/LoFi_EffectParameters.h"
#include <cstring>

namespace ProLoFi {

class LoFiDSPEngine {
public:
    LoFiDSPEngine();

    void prepare(double sampleRate);
    void reset();

    AAX_Original::LoFi_EffectParameters& getParameters() { return mParams; }
    const AAX_Original::LoFi_EffectParameters& getParameters() const { return mParams; }

    void updateParameters(bool   bypass,
                          double sampleRateNorm,
                          double antiAliasPct,
                          int    sampleSizeBits,
                          int    quantMode,
                          double noisePct,
                          double distortion,
                          double saturation);

    void processBlock(const float* const* inputs,
                      float* const*       outputs,
                      int                 numChannels,
                      int                 numSamples);

    float getInputPeak(int ch) const  { return mInputPeak[ch & 1]; }
    float getOutputPeak(int ch) const { return mOutputPeak[ch & 1]; }
    void  decayMeters(float decayFactor = 0.92f);

private:
    AAX_Original::LoFi_EffectParameters mParams;

    // AAX DSP Context & Coefficient Packets
    int32_t                          mBypassFlag = 0;
    int32_t                          mQuantMode  = 0;
    AAX_Original::LoFiSRFilterCoeffs mSRCoeffs{};
    AAX_Original::LoFiQuantCoeffs    mQuantCoeffs{};
    AAX_Original::LoFiNoiseCoeffs    mNoiseCoeffs{};
    AAX_Original::LoFiDistCoeffs     mDistCoeffs{};
    AAX_Original::LoFiSatCoeffs      mSatCoeffs{};
    AAX_Original::LoFiState          mState[2]{};
    float                            mEnvHistory[2][64]{};
    float                            mInputPeak[2]{ 0.0f, 0.0f };
    float                            mOutputPeak[2]{ 0.0f, 0.0f };
};

} // namespace ProLoFi
