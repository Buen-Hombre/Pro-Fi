#pragma once

#include "LoFiAlgDefs.h"
#include <string>
#include <vector>

namespace ProLoFi {
namespace AAX_Original {

// ============================================================================
// Reconstructed Host Data Model & Coefficient Generator from:
//   - LoFi_EffectParameters.cpp (RTTI & constants @ 0x124680..0x124900, 0x12f0a0..0x131234)
//   - LoFi.xml / LoFiGUI.xml / Taper.xml
//   - Factory Presets/*.tfx (25 factory presets)
// ============================================================================

struct LoFiPreset {
    const char* name;
    float sampleRateNorm; // 0.0 .. 1.0 (63 steps)
    float antiAliasPct;   // 0.0 .. 100.0 %
    int   sampleSizeBits; // 2 .. 24 bits
    int   quantization;   // 0 = Linear, 1 = Adaptive
    float noisePct;       // 0.0 .. 100.0 %
    float distortion;     // 0.0 .. 10.0
    float saturation;     // 0.0 .. 10.0
};

// All 25 authentic Pro Tools Lo-Fi Factory Presets decoded from Contents/Factory Presets/Lo-Fi/*.tfx
static constexpr LoFiPreset kFactoryPresets[25] = {
    { "Bass Dirty Amp",             0.899f,  68.0f, 24, 0,  0.0f, 0.8f, 0.7f },
    { "Cool Noise Mod",             1.000f, 100.0f, 24, 0, 40.1f, 0.0f, 0.3f },
    { "Cool Noise Mod 2",           1.000f, 100.0f, 24, 0, 28.1f, 1.9f, 0.3f },
    { "Digital Destruction 1",      0.892f,  37.0f, 12, 0,  0.0f, 0.0f, 0.1f },
    { "Digital Destruction 2",      0.826f,  22.0f,  7, 0,  0.0f, 0.0f, 0.1f },
    { "Digital Destruction 3",      0.940f,  39.0f,  7, 0,  0.0f, 0.0f, 0.1f },
    { "Digital Destruction 4",      0.826f,  22.0f,  7, 1,  0.0f, 0.0f, 0.1f },
    { "Digital Destruction 5",      0.563f,   0.0f, 12, 0,  0.0f, 0.0f, 0.1f },
    { "Digital Destruction Climax", 0.563f,   0.0f,  5, 0,  0.0f, 0.0f, 0.1f },
    { "Dirt Diggin'",               0.970f,  68.0f, 12, 1,  0.0f, 1.0f, 0.7f },
    { "Distortio",                  1.000f, 100.0f, 24, 0,  0.0f, 3.6f, 0.4f },
    { "Drum Loop Kaputt 1",         1.000f, 100.0f,  3, 0, 89.2f, 1.0f, 0.2f },
    { "Drum Loop Kaputt 2",         1.000f,   0.0f,  3, 0,  0.0f, 1.1f, 0.3f },
    { "Drum Loop Kaputt 3",         0.988f,  37.0f,  4, 0,  0.0f, 1.0f, 0.2f },
    { "Lo-rate Distorto Kit 1",     0.923f,   0.0f,  9, 1,  0.0f, 1.9f, 2.0f },
    { "Nasty Distortion",           0.928f, 100.0f, 24, 0,  0.0f, 6.8f, 0.0f },
    { "Nasty Distortion 2",         0.928f,  76.0f, 24, 0,  0.0f, 6.8f, 0.0f },
    { "Nasty Distortion 3",         0.964f,  76.0f, 24, 0,  0.0f, 6.8f, 0.0f },
    { "Old Converter",              0.970f,  16.0f, 12, 1,  0.0f, 0.0f, 0.0f },
    { "Overdriven",                 1.000f, 100.0f, 24, 0,  0.0f, 2.3f, 0.1f },
    { "Ring-Moddy Trash Bass",      0.102f,   7.0f,  8, 0,  0.0f, 0.7f, 0.9f },
    { "Slam Distortion",            1.000f, 100.0f, 24, 0,  0.0f, 2.9f, 5.5f },
    { "Tape Saturation",            1.000f, 100.0f, 24, 0,  0.0f, 1.1f, 0.1f },
    { "Toy Bear Audio",             0.940f,  10.0f,  8, 1,  0.0f, 0.0f, 0.0f },
    { "Trash Bass",                 0.743f,  69.0f, 19, 0,  0.0f, 2.8f, 0.6f }
};

// Display Delegate Decorators recovered from RTTI in LoFi_arm64 @ 0x1247b0..0x1249c0:
// - LoFi_SRDisplayDelegateDecorator<double, 100, 2, 0>
// - LoFi_ChangeRangeDisplayDelegate<double>
// - LoFi_RoundDisplayDelegateDecorator<double>
class LoFi_EffectParameters {
public:
    LoFi_EffectParameters();

    void setHostSampleRate(double hostSr);
    double getHostSampleRate() const { return mHostSampleRate; }

    // Parameter setters
    void setBypass(bool bypassed);
    void setSampleRateNorm(double norm01);   // 0.0 .. 1.0 (63 steps, __const @ 0x124748 = 63.0)
    void setAntiAliasPct(double pct0_100);   // 0.0 .. 100.0 %
    void setSampleSizeBits(int bits2_24);    // 2 .. 24 bits (__const @ 0x124708 = {2, 24})
    void setQuantizationMode(int mode0_1);   // 0 = Linear, 1 = Adaptive (__const @ 0x124680 = {0, 1})
    void setNoisePct(double pct0_100);       // 0.0 .. 100.0 %
    void setDistortion(double dist0_10);     // 0.0 .. 10.0
    void setSaturation(double sat0_10);      // 0.0 .. 10.0 (__const @ 0x124738 = 11.0)

    // Display formatting matching LoFi_SRDisplayDelegateDecorator & AAX_CUnitDisplayDelegateDecorator
    int         getDecimationStep() const;
    double      getEffectiveSampleRateHz() const;
    std::string formatSampleRateDisplay() const;
    std::string formatAntiAliasDisplay() const;
    std::string formatSampleSizeDisplay() const;
    std::string formatQuantizationDisplay() const;
    std::string formatNoiseDisplay() const;
    std::string formatDistortionDisplay() const;
    std::string formatSaturationDisplay() const;

    // Taper.xml piecewise linear dB meter conversion (0..197 pixels)
    static float linearPeakToMeterPixels(float peakAmplitude);

    // Populate the AAX DSP coefficient packets for AlgEntry
    void updateCoefficients(LoFiSRFilterCoeffs& srOut,
                            LoFiQuantCoeffs&    quantOut,
                            LoFiNoiseCoeffs&    noiseOut,
                            LoFiDistCoeffs&     distOut,
                            LoFiSatCoeffs&      satOut) const;

    const float* getWaveTable() const { return mWaveTable; }

private:
    void buildWaveTable();

    double mHostSampleRate = 48000.0;
    bool   mBypass         = false;
    double mSampleRateNorm = 1.0;   // Default 1.0 (max sample rate)
    double mAntiAliasPct   = 100.0; // Default 100%
    int    mSampleSizeBits = 24;    // Default 24 bits
    int    mQuantMode      = 0;     // Default 0 ("Linear")
    double mNoisePct       = 0.0;   // Default 0.0%
    double mDistortion     = 0.0;   // Default 0.0
    double mSaturation     = 0.0;   // Default 0.0

    float  mWaveTable[65];          // 65-entry distortion lookup table (*+A5[11])
};

} // namespace AAX_Original
} // namespace ProLoFi
