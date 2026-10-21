#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginProcessor.h"

namespace ProLoFi {

// ============================================================================
// ProFiWin98LookAndFeel
// Authentic late-90s Windows 98 LookAndFeel: beveled panels, 3D trackbars,
// classic radio buttons, grouped boxes, and rotary knobs with tick marks.
// ============================================================================
class ProFiWin98LookAndFeel : public juce::LookAndFeel_V4 {
public:
    ProFiWin98LookAndFeel();
    ~ProFiWin98LookAndFeel() override = default;

    void setKnobSprite(const juce::Image& img) { mKnobSprite = img; }

    static void drawWin98Bevel(juce::Graphics& g,
                               juce::Rectangle<int> r,
                               bool sunken,
                               juce::Colour fillCol = juce::Colour(192, 192, 192));

    static void drawWin98GroupBox(juce::Graphics& g,
                                  juce::Rectangle<int> r,
                                  const juce::String& text);

    void drawLinearSlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          const juce::Slider::SliderStyle style,
                          juce::Slider& slider) override;

    void drawRotarySlider(juce::Graphics& g,
                          int x, int y, int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;

    void drawButtonBackground(juce::Graphics& g,
                              juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool shouldDrawButtonAsHighlighted,
                              bool shouldDrawButtonAsDown) override;

    void drawButtonText(juce::Graphics& g,
                        juce::TextButton& button,
                        bool shouldDrawButtonAsHighlighted,
                        bool shouldDrawButtonAsDown) override;

    void drawToggleButton(juce::Graphics& g,
                          juce::ToggleButton& button,
                          bool shouldDrawButtonAsHighlighted,
                          bool shouldDrawButtonAsDown) override;

    void drawComboBox(juce::Graphics& g,
                      int width, int height,
                      bool isButtonDown,
                      int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox& box) override;

    juce::Font getComboBoxFont(juce::ComboBox&) override;
    juce::Font getPopupMenuFont() override;

private:
    juce::Image mKnobSprite;
};

// ============================================================================
// ProLoFiAudioProcessorEditor ("Pro-Fi - Lo-Fi Processor" 640x448)
// Pure Windows 98 aesthetic, minimalist, clean, responsive
// ============================================================================
class ProLoFiAudioProcessorEditor : public juce::AudioProcessorEditor,
                                    private juce::Timer {
public:
    explicit ProLoFiAudioProcessorEditor(ProLoFiAudioProcessor&);
    ~ProLoFiAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;
    void updateReadouts();

    ProLoFiAudioProcessor& mProcessor;
    ProFiWin98LookAndFeel  mWin98LnF;

    // Nano Banana visual assets
    juce::Image mKnobImage;

    // Controls
    juce::Slider       mSampleRateSlider;
    juce::Slider       mSampleSizeSlider;
    juce::Slider       mAntiAliasSlider;
    juce::ToggleButton mLinearButton;
    juce::ToggleButton mAdaptiveButton;

    juce::Slider       mDistortionKnob;
    juce::Slider       mNoiseKnob;
    juce::Slider       mSaturationKnob;

    juce::ComboBox     mPresetBox;
    juce::TextButton   mBypassButton;

    // Value Readout Labels (Win98 sunken 3D text boxes)
    juce::Label mSampleRateLabel;
    juce::Label mSampleSizeLabel;
    juce::Label mAntiAliasLabel;
    juce::Label mDistortionLabel;
    juce::Label mNoiseLabel;
    juce::Label mSaturationLabel;

    // Meter peak hold & animation
    float mPeakHold[2]   { 0.0f, 0.0f };
    bool  mClipSticky[2] { false, false };

    // APVTS Attachments
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    std::unique_ptr<SliderAttachment> mSampleRateAttachment;
    std::unique_ptr<SliderAttachment> mSampleSizeAttachment;
    std::unique_ptr<SliderAttachment> mAntiAliasAttachment;
    std::unique_ptr<SliderAttachment> mDistortionAttachment;
    std::unique_ptr<SliderAttachment> mNoiseAttachment;
    std::unique_ptr<SliderAttachment> mSaturationAttachment;
    std::unique_ptr<ButtonAttachment> mBypassAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProLoFiAudioProcessorEditor)
};

} // namespace ProLoFi
