#include "LoFiDSP.h"
#include <algorithm>

namespace ProLoFi {

LoFiDSPEngine::LoFiDSPEngine() {
    reset();
    mParams.updateCoefficients(mSRCoeffs, mQuantCoeffs, mNoiseCoeffs, mDistCoeffs, mSatCoeffs);
}

void LoFiDSPEngine::prepare(double sampleRate) {
    mParams.setHostSampleRate(sampleRate);
    reset();
    mParams.updateCoefficients(mSRCoeffs, mQuantCoeffs, mNoiseCoeffs, mDistCoeffs, mSatCoeffs);
}

void LoFiDSPEngine::reset() {
    std::memset(mState, 0, sizeof(mState));
    std::memset(mEnvHistory, 0, sizeof(mEnvHistory));
    for (int ch = 0; ch < 2; ++ch) {
        mState[ch].srHoldCounter = 1;
        mState[ch].srSubCounter  = 1;
        mState[ch].lfsrState     = 0x0055AA55u ^ static_cast<uint32_t>(ch * 0x111111u);
        mInputPeak[ch]           = 0.0f;
        mOutputPeak[ch]          = 0.0f;
    }
}

void LoFiDSPEngine::updateParameters(bool   bypass,
                                     double sampleRateNorm,
                                     double antiAliasPct,
                                     int    sampleSizeBits,
                                     int    quantMode,
                                     double noisePct,
                                     double distortion,
                                     double saturation)
{
    mBypassFlag = bypass ? 1 : 0;
    mQuantMode  = (quantMode != 0) ? 1 : 0;

    mParams.setBypass(bypass);
    mParams.setSampleRateNorm(sampleRateNorm);
    mParams.setAntiAliasPct(antiAliasPct);
    mParams.setSampleSizeBits(sampleSizeBits);
    mParams.setQuantizationMode(quantMode);
    mParams.setNoisePct(noisePct);
    mParams.setDistortion(distortion);
    mParams.setSaturation(saturation);

    mParams.updateCoefficients(mSRCoeffs, mQuantCoeffs, mNoiseCoeffs, mDistCoeffs, mSatCoeffs);
}

void LoFiDSPEngine::processBlock(const float* const* inputs,
                                 float* const*       outputs,
                                 int                 numChannels,
                                 int                 numSamples)
{
    if (numChannels <= 0 || numSamples <= 0) return;

    float inSubBlock[2][4]{};
    float outSubBlock[2][4]{};
    float* inPtrs[2]  = { inSubBlock[0],  inSubBlock[1] };
    float* outPtrs[2] = { outSubBlock[0], outSubBlock[1] };

    float* meterPtrsMono[2]   = { &mOutputPeak[0], &mInputPeak[0] };
    float* meterPtrsStereo[4] = { &mOutputPeak[0], &mOutputPeak[1], &mInputPeak[0], &mInputPeak[1] };

    AAX_Original::LoFiAlgContext ctx{};
    ctx.inputChannels   = inPtrs;
    ctx.outputChannels  = outPtrs;
    ctx.bypass          = &mBypassFlag;
    ctx.quantType       = &mQuantMode;
    ctx.srFilterCoeffs  = &mSRCoeffs;
    ctx.quantCoeffs     = &mQuantCoeffs;
    ctx.noiseCoeffs     = &mNoiseCoeffs;
    ctx.distCoeffs      = &mDistCoeffs;
    ctx.satCoeffs       = &mSatCoeffs;
    ctx.state           = mState;
    ctx.waveTable       = mParams.getWaveTable();
    ctx.envHistoryBuf   = &mEnvHistory[0][0];
    ctx.meterTapBuffers = (numChannels == 1) ? meterPtrsMono : meterPtrsStereo;

    AAX_Original::LoFiAlgContext* const instanceList[1] = { &ctx };

    int offset = 0;
    while (offset < numSamples) {
        const int chunk = std::min(4, numSamples - offset);

        for (int ch = 0; ch < std::min(numChannels, 2); ++ch) {
            for (int i = 0; i < 4; ++i) {
                inSubBlock[ch][i] = (i < chunk) ? inputs[ch][offset + i] : 0.0f;
            }
        }

        if (numChannels == 1) {
            AAX_Original::AlgEntry_Mono(instanceList, instanceList + 1);
            mInputPeak[1]  = mInputPeak[0];
            mOutputPeak[1] = mOutputPeak[0];
        } else {
            AAX_Original::AlgEntry_Stereo(instanceList, instanceList + 1);
        }

        for (int ch = 0; ch < std::min(numChannels, 2); ++ch) {
            for (int i = 0; i < chunk; ++i) {
                outputs[ch][offset + i] = outSubBlock[ch][i];
            }
        }

        offset += chunk;
    }
}

void LoFiDSPEngine::decayMeters(float decayFactor) {
    for (int ch = 0; ch < 2; ++ch) {
        mInputPeak[ch]  *= decayFactor;
        mOutputPeak[ch] *= decayFactor;
    }
}

} // namespace ProLoFi
