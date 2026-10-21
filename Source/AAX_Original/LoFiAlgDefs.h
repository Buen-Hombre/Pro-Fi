#pragma once

#include <cstdint>

namespace ProLoFi {
namespace AAX_Original {

// ============================================================================
// Exact memory layouts recovered from LoFiAlgMono.dll (0x0000..0x0f20),
// LoFiAlgStereo.dll (0x0000..0x0fa0), and LoFi_arm64 (__const 0x124680..0x124780)
// ============================================================================

// Plug-In FourCharCodes from LoFi_arm64 @ 0x124690..0x1246ec
constexpr uint32_t kManufacturerID_Digi = 0x44696769; // 'Digi'
constexpr uint32_t kProductID_LoFi      = 0x4C6F4669; // 'LoFi'

constexpr uint32_t kPlugInID_DSP_Mono        = 0x31314C46; // '11LF'
constexpr uint32_t kPlugInID_DSP_Stereo      = 0x32324C46; // '22LF'
constexpr uint32_t kPlugInID_Native_Mono     = 0x524D4C46; // 'RMLF'
constexpr uint32_t kPlugInID_Native_Stereo   = 0x52534C46; // 'RSLF'
constexpr uint32_t kPlugInID_AudioSuite_Mono = 0x41534C46; // 'ASLF'
constexpr uint32_t kPlugInID_AudioSuite_Ster = 0x41534C66; // 'ASLf'

constexpr uint32_t kMeterID_InputMono    = 0x496E704D; // 'InpM'
constexpr uint32_t kMeterID_OutputMono   = 0x4F75744D; // 'OutM'
constexpr uint32_t kMeterID_InputStereo  = 0x496E7053; // 'InpS'
constexpr uint32_t kMeterID_OutputStereo = 0x4F757453; // 'OutS'

// Adaptive Quantization step-scaling table ($P$T0$1):
// Found identically in LoFiAlgMono.dll (.const @ 0x1080),
// LoFiAlgStereo.dll (.const @ 0x1100), and LoFi_arm64 (__const @ 0x1246f0)
static constexpr float kAdaptiveQuantScaleTable[6] = {
    1.0f,       // 2^0  (B19 = 0: runningAbsSum >= 128)
    0.5f,       // 2^-1 (B19 = 1: 64 <= runningAbsSum < 128)
    0.25f,      // 2^-2 (B19 = 2: 32 <= runningAbsSum < 64)
    0.125f,     // 2^-3 (B19 = 3: 16 <= runningAbsSum < 32)
    0.0625f,    // 2^-4 (B19 = 4:  8 <= runningAbsSum < 16)
    0.03125f    // 2^-5 (B19 = 5:       runningAbsSum < 8)
};

// *+A5[5]: Sample Rate Decimation & 4th-Order (2-Biquad) Anti-Aliasing Filter Coeffs
struct LoFiSRFilterCoeffs {
    int32_t decimationStep;     // Word 0 (*+B4[0]): Hold period in samples (>= 1)
    int32_t filterEnable;       // Word 1 (*+B8[1]): 1 when anti-alias biquad cascade is active
    // Double-precision 2-stage cascaded biquad coefficients (*+B18[1..8] in 64-bit LDDW indexing):
    double b0_stage1;           // LDDW[1] (*+B28[1])
    double b1_stage1;           // LDDW[2] (*+B8[2])
    double b2_stage1;           // LDDW[3] (*+B4[3])
    double a1_stage1;           // LDDW[4] (*+B27[4])
    double a2_stage1;           // LDDW[5] (*+B18[5])
    double b_stage2;            // LDDW[6] (*+B22[6])
    double a1_stage2;           // LDDW[7] (*+B23[7])
    double a2_stage2;           // LDDW[8] (*+B27[8])
    int32_t envWindowMaxIdx;    // Word 18 (*+B26[18]): Circular buffer max index (63 for 64-sample window)
    int32_t padding;
};

// *+A5[6]: Sample Size (Bit-Depth Quantization) Coeffs
struct LoFiQuantCoeffs {
    int32_t enable;             // Word 0 (*+B24[0]): 1 when Sample Size < 24 bits
    int32_t pad0;
    double  scale;              // LDDW[1] (*+B24[1]): 2^(bits - 1)
    double  invScale;           // LDDW[2] (*+B24[2]): 2^-(bits - 1)
};

// *+A5[7]: Noise Generator Coeffs
struct LoFiNoiseCoeffs {
    int32_t enable;             // Word 0 (*+B25[0]): 1 when Noise > 0%
    int32_t pad0;
    double  envModGain;         // LDDW[1] (*+B19[1]): Noise gain scaled by envelope
};

// *+A5[8]: Waveshaping Distortion Coeffs
struct LoFiDistCoeffs {
    float   drive;              // Word 0 (*+A29[0]): Table index drive multiplier
    float   wetMix;             // Word 1 (*+A29[1]): Wet waveshaper gain
    float   dryMix;             // Word 2 (*+A29[2]): Dry clean gain
    int32_t enable;             // Word 3 (*+A29[3]): 1 when Distortion > 0.0
};

// *+A5[9]: Soft-Knee / Slew Saturation Coeffs
struct LoFiSatCoeffs {
    double  threshold;          // LDDW[0] (*+B27[0]): Linear region threshold T
    double  kneeSlope;          // LDDW[1] (*+B30[1]): Slope k above threshold T
    double  postGain;           // LDDW[2] (*+B4[2]):  Post-saturation makeup/attenuation gain
    int32_t enable;             // Word 6  (*+B24[6]): 1 when Saturation > 0.0
    int32_t pad0;
};

// *+A5[10]: Persistent Per-Channel / Per-Instance DSP State (A31)
struct LoFiState {
    int32_t  envHistoryIdx;     // Word 0  (*+A31[0]): Current index (0..63) in envHistory[]
    int32_t  pad1[2];
    int32_t  srHoldCounter;     // Word 3  (*+A31[3]): Primary sample-hold counter
    int32_t  pad4;
    int32_t  srSubCounter;      // Word 5  (*+A31[5]): Secondary sample-hold state
    int32_t  pad6;
    uint32_t lfsrState;         // Word 7  (*+A31[7]): 24-bit data-driven shift register state
    int32_t  pad8;
    float    heldSample;        // Word 9  (*+A31[9]): Currently held sample for SR decimation
    int32_t  pad10[2];

    // Biquad cascade delay states (accessed via LDDW/STW on A31):
    double   biquad1_x1;        // Words 6..7   (LDDW *+A31[3] / *+A31[6..7])
    double   biquad1_x2;        // Words 8..9   (LDDW *+A31[4] / *+A31[8..9])
    double   biquad1_y1;        // Words 10..11 (LDDW *+A31[5] / *+A31[10..11])
    double   biquad1_y2;        // Words 12..13 (LDDW *+A31[6] / *+A31[12..13])
    double   biquad2_y1;        // Words 14..15 (LDDW *+A31[7] / *+A31[14..15])
    double   biquad2_y2;        // Words 16..17 (LDDW *+A31[8] / *+A31[16..17])

    // Saturation state & Sliding-window envelope accumulator:
    double   prevSatState;      // LDDW *+A31[18] (Words 36..37): Previous saturation output s_{n-1}
    double   runningAbsSum;     // LDDW *+A31[20] (Words 40..41): Sliding sum of 64 |in[n]| samples
};

// AAX Algorithm Context Structure (*A5 in LoFiAlgMono.dll, *B4 in LoFiAlgStereo.dll)
struct LoFiAlgContext {
    float**             inputChannels;   // *+A5[0]: Pointer to array of input channel buffer pointers
    float**             outputChannels;  // *+A5[1]: Pointer to array of output channel buffer pointers
    void*               reserved2;       // *+A5[2]: Unused
    int32_t*            bypass;          // *+A5[3]: Master Bypass flag (0 = active, 1 = bypassed)
    int32_t*            quantType;       // *+A5[4]: Quantization mode (0 = Linear, 1 = Adaptive)
    LoFiSRFilterCoeffs* srFilterCoeffs;  // *+A5[5]: Sample Rate & Anti-Aliasing filter coefficients
    LoFiQuantCoeffs*    quantCoeffs;     // *+A5[6]: Sample Size (bit depth) coefficients
    LoFiNoiseCoeffs*    noiseCoeffs;     // *+A5[7]: Noise injection coefficients
    LoFiDistCoeffs*     distCoeffs;      // *+A5[8]: Distortion waveshaper coefficients
    LoFiSatCoeffs*      satCoeffs;       // *+A5[9]: Saturation coefficients
    LoFiState*          state;           // *+A5[10]: Persistent DSP state (1 per channel)
    const float*        waveTable;       // *+A5[11]: 65-entry distortion lookup table (float[65])
    float*              envHistoryBuf;   // *+A5[12]: 64-sample circular buffer for envelope (float[64] per ch)
    float**             meterTapBuffers; // *+A5[13]: Meter tap pointers ([0] = Output peak, [1] = Input peak)
};

// Entry points matching LoFiAlgMono.dll and LoFiAlgStereo.dll
void AlgEntry_Mono(LoFiAlgContext* const* instanceListBegin,
                   LoFiAlgContext* const* instanceListEnd);

void AlgEntry_Stereo(LoFiAlgContext* const* instanceListBegin,
                     LoFiAlgContext* const* instanceListEnd);

} // namespace AAX_Original
} // namespace ProLoFi
