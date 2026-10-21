#include "PluginEditor.h"
#include "ProFiBinaryData.h"
#include <cmath>

namespace ProLoFi {

namespace {

static juce::Font makeWin98Font(float height, bool bold = false) {
    return juce::Font(juce::FontOptions("MS Sans Serif", height, bold ? juce::Font::bold : juce::Font::plain));
}

static void setupSunkenReadout(juce::Label& lbl) {
    lbl.setJustificationType(juce::Justification::centred);
    lbl.setColour(juce::Label::textColourId, juce::Colour(0, 0, 0));
    lbl.setColour(juce::Label::backgroundColourId, juce::Colour(255, 255, 255));
    lbl.setColour(juce::Label::outlineColourId, juce::Colour(128, 128, 128));
    lbl.setFont(makeWin98Font(11.5f, true));
}

} // anonymous namespace

// ============================================================================
// ProFiWin98LookAndFeel Implementation
// ============================================================================
ProFiWin98LookAndFeel::ProFiWin98LookAndFeel() {
    setColour(juce::PopupMenu::backgroundColourId,            juce::Colour(192, 192, 192));
    setColour(juce::PopupMenu::textColourId,                  juce::Colour(0, 0, 0));
    setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour(0, 0, 128));
    setColour(juce::PopupMenu::highlightedTextColourId,       juce::Colour(255, 255, 255));
    setColour(juce::ComboBox::backgroundColourId,             juce::Colour(255, 255, 255));
    setColour(juce::ComboBox::textColourId,                   juce::Colour(0, 0, 0));
    setColour(juce::ComboBox::outlineColourId,                juce::Colour(128, 128, 128));
}

void ProFiWin98LookAndFeel::drawWin98Bevel(juce::Graphics& g,
                                           juce::Rectangle<int> r,
                                           bool sunken,
                                           juce::Colour fillCol)
{
    g.setColour(fillCol);
    g.fillRect(r);

    const juce::Colour outerTL = sunken ? juce::Colour(128, 128, 128) : juce::Colour(255, 255, 255);
    const juce::Colour innerTL = sunken ? juce::Colour(0, 0, 0)       : juce::Colour(223, 223, 223);
    const juce::Colour outerBR = sunken ? juce::Colour(255, 255, 255) : juce::Colour(0, 0, 0);
    const juce::Colour innerBR = sunken ? juce::Colour(223, 223, 223) : juce::Colour(128, 128, 128);

    const int x = r.getX(), y = r.getY(), w = r.getWidth(), h = r.getHeight();
    if (w < 4 || h < 4) return;

    // Outer top-left
    g.setColour(outerTL);
    g.drawHorizontalLine(y, static_cast<float>(x), static_cast<float>(x + w - 1));
    g.drawVerticalLine(x, static_cast<float>(y), static_cast<float>(y + h - 1));

    // Inner top-left
    g.setColour(innerTL);
    g.drawHorizontalLine(y + 1, static_cast<float>(x + 1), static_cast<float>(x + w - 2));
    g.drawVerticalLine(x + 1, static_cast<float>(y + 1), static_cast<float>(y + h - 2));

    // Inner bottom-right
    g.setColour(innerBR);
    g.drawHorizontalLine(y + h - 2, static_cast<float>(x + 1), static_cast<float>(x + w - 1));
    g.drawVerticalLine(x + w - 2, static_cast<float>(y + 1), static_cast<float>(y + h - 1));

    // Outer bottom-right
    g.setColour(outerBR);
    g.drawHorizontalLine(y + h - 1, static_cast<float>(x), static_cast<float>(x + w));
    g.drawVerticalLine(x + w - 1, static_cast<float>(y), static_cast<float>(y + h));
}

void ProFiWin98LookAndFeel::drawWin98GroupBox(juce::Graphics& g,
                                              juce::Rectangle<int> r,
                                              const juce::String& text)
{
    const int textPad = 8;
    const int fontH = 12;
    juce::Font font = makeWin98Font(11.5f, true);
    juce::GlyphArrangement ga;
    ga.addLineOfText(font, text, 0.0f, 0.0f);
    const int textW = static_cast<int>(std::ceil(ga.getBoundingBox(0, -1, true).getWidth()));

    const int topY = r.getY() + fontH / 2;
    const int boxX = r.getX();
    const int boxW = r.getWidth();
    const int boxH = r.getHeight() - (fontH / 2);

    // 3D Etched rectangle (gray inner line + white outer highlight line)
    // Dark line
    g.setColour(juce::Colour(128, 128, 128));
    g.drawHorizontalLine(topY, static_cast<float>(boxX), static_cast<float>(boxX + textPad));
    g.drawHorizontalLine(topY, static_cast<float>(boxX + textPad + textW + 4), static_cast<float>(boxX + boxW - 1));
    g.drawVerticalLine(boxX, static_cast<float>(topY), static_cast<float>(topY + boxH - 1));
    g.drawVerticalLine(boxX + boxW - 2, static_cast<float>(topY), static_cast<float>(topY + boxH - 1));
    g.drawHorizontalLine(topY + boxH - 2, static_cast<float>(boxX), static_cast<float>(boxX + boxW - 1));

    // Light highlight line (1px offset)
    g.setColour(juce::Colour(255, 255, 255));
    g.drawHorizontalLine(topY + 1, static_cast<float>(boxX + 1), static_cast<float>(boxX + textPad));
    g.drawHorizontalLine(topY + 1, static_cast<float>(boxX + textPad + textW + 4), static_cast<float>(boxX + boxW - 2));
    g.drawVerticalLine(boxX + 1, static_cast<float>(topY + 1), static_cast<float>(topY + boxH - 2));
    g.drawVerticalLine(boxX + boxW - 1, static_cast<float>(topY), static_cast<float>(topY + boxH));
    g.drawHorizontalLine(topY + boxH - 1, static_cast<float>(boxX), static_cast<float>(boxX + boxW));

    // Text Header
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(font);
    g.drawText(text, boxX + textPad + 2, r.getY(), textW, fontH, juce::Justification::centredLeft);
}

void ProFiWin98LookAndFeel::drawLinearSlider(juce::Graphics& g,
                                             int x, int y, int width, int height,
                                             float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
                                             const juce::Slider::SliderStyle /*style*/,
                                             juce::Slider& /*slider*/)
{
    // Authentic Windows 98 Horizontal Trackbar with Groove, 3D Thumb and Tick Marks
    const int midY = y + 7;
    const int grooveH = 4;
    const juce::Rectangle<int> groove(x + 4, midY, width - 8, grooveH);

    // Sunken 3D Groove
    g.setColour(juce::Colour(128, 128, 128));
    g.drawHorizontalLine(groove.getY(), static_cast<float>(groove.getX()), static_cast<float>(groove.getRight() - 1));
    g.drawVerticalLine(groove.getX(), static_cast<float>(groove.getY()), static_cast<float>(groove.getBottom() - 1));
    g.setColour(juce::Colour(255, 255, 255));
    g.drawHorizontalLine(groove.getBottom() - 1, static_cast<float>(groove.getX()), static_cast<float>(groove.getRight()));
    g.drawVerticalLine(groove.getRight() - 1, static_cast<float>(groove.getY()), static_cast<float>(groove.getBottom()));
    g.setColour(juce::Colour(0, 0, 0));
    g.fillRect(groove.getX() + 1, groove.getY() + 1, groove.getWidth() - 2, groove.getHeight() - 2);

    // Tick Marks below the trackbar
    const int numTicks = 11;
    const int tickTop = midY + 9;
    g.setColour(juce::Colour(0, 0, 0));
    for (int i = 0; i < numTicks; ++i) {
        const float tx = groove.getX() + (static_cast<float>(i) / (numTicks - 1)) * groove.getWidth();
        g.drawVerticalLine(static_cast<int>(std::round(tx)), static_cast<float>(tickTop), static_cast<float>(tickTop + 4));
    }

    // Windows 98 Pointed Trackbar Thumb (Width: 11, Height: 18)
    const float thumbW = 11.0f;
    const float thumbH = 18.0f;
    const float thumbX = juce::jlimit(static_cast<float>(groove.getX()),
                                      static_cast<float>(groove.getRight()),
                                      sliderPos) - thumbW * 0.5f;
    const float thumbY = static_cast<float>(y);

    juce::Path thumb;
    thumb.startNewSubPath(thumbX, thumbY);
    thumb.lineTo(thumbX + thumbW, thumbY);
    thumb.lineTo(thumbX + thumbW, thumbY + 12.0f);
    thumb.lineTo(thumbX + thumbW * 0.5f, thumbY + thumbH);
    thumb.lineTo(thumbX, thumbY + 12.0f);
    thumb.closeSubPath();

    g.setColour(juce::Colour(192, 192, 192));
    g.fillPath(thumb);

    // Bevel edges on thumb
    g.setColour(juce::Colour(255, 255, 255));
    g.drawLine(thumbX, thumbY, thumbX + thumbW, thumbY, 1.0f);
    g.drawLine(thumbX, thumbY, thumbX, thumbY + 12.0f, 1.0f);
    g.drawLine(thumbX, thumbY + 12.0f, thumbX + thumbW * 0.5f, thumbY + thumbH, 1.0f);

    g.setColour(juce::Colour(0, 0, 0));
    g.drawLine(thumbX + thumbW, thumbY, thumbX + thumbW, thumbY + 12.0f, 1.0f);
    g.drawLine(thumbX + thumbW, thumbY + 12.0f, thumbX + thumbW * 0.5f, thumbY + thumbH, 1.0f);
}

void ProFiWin98LookAndFeel::drawRotarySlider(juce::Graphics& g,
                                             int x, int y, int width, int height,
                                             float sliderPosProportional,
                                             float rotaryStartAngle,
                                             float rotaryEndAngle,
                                             juce::Slider& /*slider*/)
{
    const float cx = x + width * 0.5f;
    const float cy = y + height * 0.5f - 4.0f;
    const float radius = juce::jmin(width, height) * 0.5f - 14.0f;
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    // Draw 11 Windows 98 radial tick marks around dial
    for (int i = 0; i <= 10; ++i) {
        const float t = static_cast<float>(i) / 10.0f;
        const float a = rotaryStartAngle + t * (rotaryEndAngle - rotaryStartAngle) - juce::MathConstants<float>::halfPi;
        const float r1 = radius + 3.0f;
        const float r2 = radius + 7.0f;
        const bool lit = (t <= sliderPosProportional + 0.005f);

        // Highlight/shadow effect on ticks
        g.setColour(lit ? juce::Colour(0, 128, 0) : juce::Colour(80, 80, 80));
        g.drawLine(cx + std::cos(a) * r1, cy + std::sin(a) * r1,
                   cx + std::cos(a) * r2, cy + std::sin(a) * r2,
                   lit ? 2.0f : 1.2f);
    }

    // Draw Nano Banana Win98 knob dial sprite
    if (mKnobSprite.isValid()) {
        const float spriteSize = radius * 2.05f;
        const float scale = spriteSize / static_cast<float>(mKnobSprite.getWidth());
        juce::AffineTransform xf = juce::AffineTransform::translation(
                                       -mKnobSprite.getWidth() * 0.5f,
                                       -mKnobSprite.getHeight() * 0.5f)
                                   .rotated(angle)
                                   .scaled(scale, scale)
                                   .translated(cx, cy);
        g.drawImageTransformed(mKnobSprite, xf, false);
    } else {
        // Fallback procedural Win98 dial
        g.setColour(juce::Colour(192, 192, 192));
        g.fillEllipse(cx - radius, cy - radius, radius * 2.0f, radius * 2.0f);
        drawWin98Bevel(g, juce::Rectangle<int>(static_cast<int>(cx - radius), static_cast<int>(cy - radius),
                                               static_cast<int>(radius * 2), static_cast<int>(radius * 2)), false);
    }

    // Crisp Windows 98 indicator needle & central green cap dot
    const float dirAngle = angle - juce::MathConstants<float>::halfPi;
    const float p1x = cx + std::cos(dirAngle) * (radius * 0.15f);
    const float p1y = cy + std::sin(dirAngle) * (radius * 0.15f);
    const float p2x = cx + std::cos(dirAngle) * (radius * 0.72f);
    const float p2y = cy + std::sin(dirAngle) * (radius * 0.72f);

    g.setColour(juce::Colour(255, 255, 255));
    g.drawLine(p1x + 1.0f, p1y + 1.0f, p2x + 1.0f, p2y + 1.0f, 2.5f);
    g.setColour(juce::Colour(0, 0, 128));
    g.drawLine(p1x, p1y, p2x, p2y, 2.5f);
    g.setColour(juce::Colour(0, 200, 50));
    g.fillEllipse(p2x - 2.5f, p2y - 2.5f, 5.0f, 5.0f);
}

void ProFiWin98LookAndFeel::drawButtonBackground(juce::Graphics& g,
                                                 juce::Button& button,
                                                 const juce::Colour& /*backgroundColour*/,
                                                 bool /*shouldDrawButtonAsHighlighted*/,
                                                 bool shouldDrawButtonAsDown)
{
    const bool toggled = button.getToggleState();
    const bool sunken  = shouldDrawButtonAsDown || toggled;
    const juce::Colour fill = toggled ? juce::Colour(214, 218, 226) : juce::Colour(192, 192, 192);
    drawWin98Bevel(g, button.getLocalBounds(), sunken, fill);

    if (toggled) {
        g.setColour(juce::Colour(0, 0, 128));
        g.drawRect(button.getLocalBounds().reduced(3), 1);
    }
}

void ProFiWin98LookAndFeel::drawButtonText(juce::Graphics& g,
                                           juce::TextButton& button,
                                           bool /*shouldDrawButtonAsHighlighted*/,
                                           bool shouldDrawButtonAsDown)
{
    const bool toggled = button.getToggleState();
    const int offset = (shouldDrawButtonAsDown || toggled) ? 1 : 0;
    auto r = button.getLocalBounds().translated(offset, offset);

    // Draw small LED indicator on Bypass button
    if (button.getComponentID() == "BypassBtn") {
        const int ledY = r.getCentreY() - 3;
        const int ledX = r.getX() + 6;
        const juce::Colour ledCol = toggled ? juce::Colour(255, 30, 30) : juce::Colour(0, 200, 50);
        g.setColour(juce::Colour(0, 0, 0));
        g.fillRect(ledX - 1, ledY - 1, 8, 8);
        g.setColour(ledCol);
        g.fillRect(ledX, ledY, 6, 6);
        r = r.withTrimmedLeft(14);
    }

    g.setColour(toggled ? juce::Colour(0, 0, 128) : juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(11.0f, true));
    g.drawText(button.getButtonText(), r, juce::Justification::centred, false);
}

void ProFiWin98LookAndFeel::drawToggleButton(juce::Graphics& g,
                                             juce::ToggleButton& button,
                                             bool /*shouldDrawButtonAsHighlighted*/,
                                             bool /*shouldDrawButtonAsDown*/)
{
    const int diameter = 12;
    const int cy = button.getHeight() / 2;
    const int cx = 4;
    const bool isOn = button.getToggleState();

    // Authentic Windows 98 3D Radio Button Circle
    g.setColour(juce::Colour(128, 128, 128));
    g.drawEllipse(cx, cy - diameter / 2, diameter, diameter, 1.0f);
    g.setColour(juce::Colour(255, 255, 255));
    g.fillEllipse(cx + 1, cy - diameter / 2 + 1, diameter - 2, diameter - 2);
    // Inner 3D border
    g.setColour(juce::Colour(64, 64, 64));
    g.drawEllipse(static_cast<float>(cx + 1), static_cast<float>(cy - diameter / 2 + 1),
                  static_cast<float>(diameter - 2), static_cast<float>(diameter - 2), 1.0f);

    // Inner selected radio dot
    if (isOn) {
        g.setColour(juce::Colour(0, 0, 0));
        g.fillEllipse(cx + 3.5f, cy - 2.5f, 5.0f, 5.0f);
    }

    // Button label
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(11.5f, false));
    g.drawText(button.getButtonText(),
               cx + diameter + 6, 0, button.getWidth() - (cx + diameter + 6), button.getHeight(),
               juce::Justification::centredLeft);
}

void ProFiWin98LookAndFeel::drawComboBox(juce::Graphics& g,
                                         int width, int height,
                                         bool isButtonDown,
                                         int /*buttonX*/, int /*buttonY*/, int /*buttonW*/, int /*buttonH*/,
                                         juce::ComboBox& /*box*/)
{
    const juce::Rectangle<int> bounds(0, 0, width, height);
    drawWin98Bevel(g, bounds, true, juce::Colour(255, 255, 255));

    const int btnW = 16;
    const juce::Rectangle<int> dropBtn(width - btnW - 2, 2, btnW, height - 4);
    drawWin98Bevel(g, dropBtn, isButtonDown, juce::Colour(192, 192, 192));

    g.setColour(juce::Colour(0, 0, 0));
    juce::Path arrow;
    const float cx = static_cast<float>(dropBtn.getCentreX());
    const float cy = static_cast<float>(dropBtn.getCentreY());
    arrow.addTriangle(cx - 3.5f, cy - 1.5f, cx + 3.5f, cy - 1.5f, cx, cy + 2.5f);
    g.fillPath(arrow);
}

juce::Font ProFiWin98LookAndFeel::getComboBoxFont(juce::ComboBox&) {
    return makeWin98Font(11.5f, true);
}

juce::Font ProFiWin98LookAndFeel::getPopupMenuFont() {
    return makeWin98Font(11.5f, false);
}

// ============================================================================
// ProLoFiAudioProcessorEditor Implementation
// ============================================================================
ProLoFiAudioProcessorEditor::ProLoFiAudioProcessorEditor(ProLoFiAudioProcessor& p)
    : AudioProcessorEditor(&p), mProcessor(p)
{
    // Load Nano Banana Win98 knob sprite from embedded binary
    mKnobImage = juce::ImageFileFormat::loadFrom(ProFiAssets::kKnobWin98Png, ProFiAssets::kKnobWin98PngSize);
    mWin98LnF.setKnobSprite(mKnobImage);
    setLookAndFeel(&mWin98LnF);

    // Compact, clean, minimalist Windows 98 dialog size: 640 x 448
    setSize(640, 448);

    // 1. Toolbar Controls: Presets ComboBox & Bypass Button
    mPresetBox.setTextWhenNothingSelected("Select Factory Preset...");
    for (int i = 0; i < mProcessor.getNumPrograms(); ++i) {
        mPresetBox.addItem(mProcessor.getProgramName(i), i + 1);
    }
    mPresetBox.onChange = [this]() {
        const int idx = mPresetBox.getSelectedItemIndex();
        if (idx >= 0) {
            mProcessor.setCurrentProgram(idx);
            updateReadouts();
        }
    };
    addAndMakeVisible(mPresetBox);

    mBypassButton.setComponentID("BypassBtn");
    mBypassButton.setClickingTogglesState(true);
    mBypassButton.setButtonText("Bypass");
    addAndMakeVisible(mBypassButton);
    mBypassAttachment = std::make_unique<ButtonAttachment>(mProcessor.getAPVTS(), "Bypass", mBypassButton);

    // 2. Panel 1: Sampling & Bit-Depth Controls
    mSampleRateSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mSampleRateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mSampleRateSlider);
    mSampleRateAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "SampleRate", mSampleRateSlider);

    mSampleSizeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mSampleSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mSampleSizeSlider);
    mSampleSizeAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "SampleSize", mSampleSizeSlider);

    mAntiAliasSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    mAntiAliasSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mAntiAliasSlider);
    mAntiAliasAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "AntiAlias", mAntiAliasSlider);

    // Radio buttons: Linear vs Adaptive
    mLinearButton.setButtonText("Linear");
    mAdaptiveButton.setButtonText("Adaptive");
    mLinearButton.setRadioGroupId(101);
    mAdaptiveButton.setRadioGroupId(101);
    mLinearButton.onClick = [this]() {
        if (auto* param = mProcessor.getAPVTS().getParameter("Quantization")) {
            param->setValueNotifyingHost(0.0f);
        }
        updateReadouts();
    };
    mAdaptiveButton.onClick = [this]() {
        if (auto* param = mProcessor.getAPVTS().getParameter("Quantization")) {
            param->setValueNotifyingHost(1.0f);
        }
        updateReadouts();
    };
    addAndMakeVisible(mLinearButton);
    addAndMakeVisible(mAdaptiveButton);

    // Sunken readouts for panel 1
    setupSunkenReadout(mSampleRateLabel);
    setupSunkenReadout(mSampleSizeLabel);
    setupSunkenReadout(mAntiAliasLabel);
    addAndMakeVisible(mSampleRateLabel);
    addAndMakeVisible(mSampleSizeLabel);
    addAndMakeVisible(mAntiAliasLabel);

    // 3. Panel 2: Grunge & Color Rotary Knobs
    mDistortionKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mDistortionKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mDistortionKnob);
    mDistortionAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "Distortion", mDistortionKnob);

    mNoiseKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mNoiseKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mNoiseKnob);
    mNoiseAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "Noise", mNoiseKnob);

    mSaturationKnob.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    mSaturationKnob.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    addAndMakeVisible(mSaturationKnob);
    mSaturationAttachment = std::make_unique<SliderAttachment>(mProcessor.getAPVTS(), "Saturation", mSaturationKnob);

    // Sunken readouts for knobs
    setupSunkenReadout(mDistortionLabel);
    setupSunkenReadout(mNoiseLabel);
    setupSunkenReadout(mSaturationLabel);
    addAndMakeVisible(mDistortionLabel);
    addAndMakeVisible(mNoiseLabel);
    addAndMakeVisible(mSaturationLabel);

    updateReadouts();
    startTimerHz(30);
}

ProLoFiAudioProcessorEditor::~ProLoFiAudioProcessorEditor() {
    stopTimer();
    setLookAndFeel(nullptr);
}

void ProLoFiAudioProcessorEditor::updateReadouts() {
    const auto& params = mProcessor.getDSPEngine().getParameters();
    mSampleRateLabel.setText(params.formatSampleRateDisplay(), juce::dontSendNotification);
    mSampleSizeLabel.setText(params.formatSampleSizeDisplay(), juce::dontSendNotification);
    mAntiAliasLabel.setText(params.formatAntiAliasDisplay(), juce::dontSendNotification);
    mDistortionLabel.setText(params.formatDistortionDisplay(), juce::dontSendNotification);
    mNoiseLabel.setText(params.formatNoiseDisplay(), juce::dontSendNotification);
    mSaturationLabel.setText(params.formatSaturationDisplay(), juce::dontSendNotification);

    const bool isAdaptive = mProcessor.getAPVTS().getRawParameterValue("Quantization")->load() >= 0.5f;
    mLinearButton.setToggleState(!isAdaptive, juce::dontSendNotification);
    mAdaptiveButton.setToggleState(isAdaptive, juce::dontSendNotification);

    const bool bypassed = mProcessor.getAPVTS().getRawParameterValue("Bypass")->load() >= 0.5f;
    mBypassButton.setButtonText(bypassed ? "Bypassed" : "Bypass");
}

void ProLoFiAudioProcessorEditor::timerCallback() {
    updateReadouts();
    mProcessor.getDSPEngine().decayMeters(0.88f);
    // Repaint meters & status bar
    repaint(452, 60, 176, 356);
    repaint(0, 422, 640, 26);
}

void ProLoFiAudioProcessorEditor::paint(juce::Graphics& g) {
    // 1. Classic Windows 98 Dialog Background (#C0C0C0) & Outer Window Bevel
    g.fillAll(juce::Colour(192, 192, 192));
    ProFiWin98LookAndFeel::drawWin98Bevel(g, getLocalBounds(), false);

    // 2. Windows 98 Title Bar: Gradient #000080 (Navy) to #1084D0 (Teal)
    const juce::Rectangle<int> titleBar(4, 4, getWidth() - 8, 20);
    juce::ColourGradient grad(juce::Colour(0, 0, 128), 4.0f, 4.0f,
                              juce::Colour(16, 132, 208), static_cast<float>(titleBar.getRight()), 4.0f, false);
    g.setGradientFill(grad);
    g.fillRect(titleBar);

    // Title Icon & Text
    g.setColour(juce::Colour(0, 255, 128));
    g.fillEllipse(8, 7, 14, 14);
    g.setColour(juce::Colour(0, 0, 128));
    g.fillRect(11, 11, 8, 6);

    g.setColour(juce::Colour(255, 255, 255));
    g.setFont(makeWin98Font(11.5f, true));
    g.drawText("Pro-Fi - Lo-Fi Processor", 26, 4, 300, 20, juce::Justification::centredLeft);

    // Close [X] and Minimize [_] buttons on title bar
    const int btnTop = 6;
    const juce::Rectangle<int> closeBtn(titleBar.getRight() - 18, btnTop, 16, 14);
    const juce::Rectangle<int> minBtn(closeBtn.getX() - 18, btnTop, 16, 14);
    ProFiWin98LookAndFeel::drawWin98Bevel(g, closeBtn, false);
    ProFiWin98LookAndFeel::drawWin98Bevel(g, minBtn, false);

    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(10.0f, true));
    g.drawText("_", minBtn.getX(), minBtn.getY() - 4, minBtn.getWidth(), minBtn.getHeight(), juce::Justification::centred);
    g.drawText("X", closeBtn.getX(), closeBtn.getY(), closeBtn.getWidth(), closeBtn.getHeight(), juce::Justification::centred);

    // 3. Preset Toolbar Label
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(11.5f, false));
    g.drawText("Preset:", 14, 30, 48, 22, juce::Justification::centredLeft);

    // 4. Panel 1: "Sampling & Bit-Depth" Group Box (x=12, y=58, w=430, h=182)
    const juce::Rectangle<int> group1(12, 58, 430, 182);
    ProFiWin98LookAndFeel::drawWin98GroupBox(g, group1, "Sampling & Bit-Depth");

    // Labels for Panel 1
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(11.5f, false));
    g.drawText("Sample Rate", 22, 78, 80, 22, juce::Justification::centredLeft);
    g.drawText("Sample Size", 22, 114, 80, 22, juce::Justification::centredLeft);
    g.drawText("Anti-Alias",  22, 150, 80, 22, juce::Justification::centredLeft);
    g.drawText("Quantization Mode:", 22, 192, 120, 22, juce::Justification::centredLeft);

    // 5. Panel 2: "Grunge & Color" Group Box (x=12, y=248, w=430, h=168)
    const juce::Rectangle<int> group2(12, 248, 430, 168);
    ProFiWin98LookAndFeel::drawWin98GroupBox(g, group2, "Grunge & Color");

    // Knob Labels
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(11.5f, true));
    g.drawText("Distortion",  40, 266, 105, 16, juce::Justification::centred);
    g.drawText("Noise",      174, 266, 105, 16, juce::Justification::centred);
    g.drawText("Saturation", 308, 266, 105, 16, juce::Justification::centred);

    // 6. Panel 3: "Output Meters" Group Box (x=452, y=58, w=176, h=358)
    const juce::Rectangle<int> group3(452, 58, 176, 358);
    ProFiWin98LookAndFeel::drawWin98GroupBox(g, group3, "Output Meters");

    // Top "dB" label
    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(10.5f, true));
    g.drawText("dB", 452, 74, 176, 14, juce::Justification::centred);

    // Authentic Windows 98 Dual LED Ladder VU Meters
    // Segmented LEDs: 24 rectangular segments per channel (Green, Yellow, Red)
    const int meterTop    = 92;
    const int meterBottom = 380;
    const int meterH      = meterBottom - meterTop;
    const int numLeds     = 24;
    const int ledH        = 10;
    const int ledSpacing  = 2;
    const int colW        = 22;
    const int leftColX    = 476;
    const int rightColX   = 582;

    const float peaks[2] = {
        mProcessor.getDSPEngine().getOutputPeak(0),
        mProcessor.getDSPEngine().getOutputPeak(1)
    };

    // Central dB Scale markings
    struct DbMark { float db; const char* txt; };
    static constexpr DbMark kDbMarks[] = {
        {   0.0f, "0" },
        {  -6.0f, "-6" },
        { -12.0f, "-12" },
        { -24.0f, "-24" },
        { -36.0f, "-36" },
        { -48.0f, "-48" }
    };

    g.setFont(makeWin98Font(9.5f, false));
    for (const auto& dm : kDbMarks) {
        const float lin = std::pow(10.0f, dm.db / 20.0f);
        const float px197 = AAX_Original::LoFi_EffectParameters::linearPeakToMeterPixels(lin);
        const float norm = px197 / 197.0f;
        const int yPos = meterBottom - static_cast<int>(std::round(norm * meterH));
        g.setColour(juce::Colour(0, 0, 0));
        g.drawText(dm.txt, leftColX + colW + 2, yPos - 6, rightColX - (leftColX + colW + 4), 12, juce::Justification::centred);
    }

    // Draw LED ladders for L and R
    for (int ch = 0; ch < 2; ++ch) {
        const int colX = (ch == 0) ? leftColX : rightColX;

        // Sunken dark well background
        const juce::Rectangle<int> well(colX - 2, meterTop - 2, colW + 4, meterH + 4);
        ProFiWin98LookAndFeel::drawWin98Bevel(g, well, true, juce::Colour(24, 28, 26));

        // Peak hold
        if (peaks[ch] >= mPeakHold[ch]) {
            mPeakHold[ch] = peaks[ch];
        } else {
            mPeakHold[ch] *= 0.985f;
        }

        const float px197 = AAX_Original::LoFi_EffectParameters::linearPeakToMeterPixels(peaks[ch]);
        const int litSegments = static_cast<int>(std::round((px197 / 197.0f) * numLeds));
        const float holdPx197 = AAX_Original::LoFi_EffectParameters::linearPeakToMeterPixels(mPeakHold[ch]);
        const int holdSeg = static_cast<int>(std::round((holdPx197 / 197.0f) * numLeds));

        for (int s = 0; s < numLeds; ++s) {
            const int segY = meterBottom - (s + 1) * (ledH + ledSpacing) + ledSpacing;
            const bool isLit = (s < litSegments);
            const bool isHold = (s == holdSeg && holdSeg > 0);

            juce::Colour onCol;
            juce::Colour offCol;
            if (s >= 21) {
                // Red clip zone (top 3)
                onCol  = juce::Colour(255, 30, 30);
                offCol = juce::Colour(75, 18, 18);
            } else if (s >= 16) {
                // Yellow warning zone (middle 5)
                onCol  = juce::Colour(250, 210, 20);
                offCol = juce::Colour(75, 65, 15);
            } else {
                // Green normal zone (bottom 16)
                onCol  = juce::Colour(0, 220, 50);
                offCol = juce::Colour(15, 65, 25);
            }

            g.setColour(isLit || isHold ? onCol : offCol);
            g.fillRect(colX, segY, colW, ledH);
            g.setColour(juce::Colour(0, 0, 0));
            g.drawRect(colX, segY, colW, ledH, 1);
        }

        // Channel identifier
        g.setColour(juce::Colour(0, 0, 0));
        g.setFont(makeWin98Font(11.0f, true));
        g.drawText((ch == 0) ? "L" : "R", colX, meterBottom + 6, colW, 16, juce::Justification::centred);
    }

    // 7. Bottom Windows 98 Status Bar
    const int statY = 424;
    const int statH = 20;
    const auto& dspParams = mProcessor.getDSPEngine().getParameters();
    const int decStep = dspParams.getDecimationStep();
    const bool bypassed = mProcessor.getAPVTS().getRawParameterValue("Bypass")->load() >= 0.5f;

    const juce::Rectangle<int> sb1(4, statY, 170, statH);
    const juce::Rectangle<int> sb2(178, statY, 214, statH);
    const juce::Rectangle<int> sb3(396, statY, 126, statH);
    const juce::Rectangle<int> sb4(526, statY, getWidth() - 530, statH);

    ProFiWin98LookAndFeel::drawWin98Bevel(g, sb1, true, juce::Colour(192, 192, 192));
    ProFiWin98LookAndFeel::drawWin98Bevel(g, sb2, true, juce::Colour(192, 192, 192));
    ProFiWin98LookAndFeel::drawWin98Bevel(g, sb3, true, juce::Colour(192, 192, 192));
    ProFiWin98LookAndFeel::drawWin98Bevel(g, sb4, true, juce::Colour(192, 192, 192));

    g.setColour(juce::Colour(0, 0, 0));
    g.setFont(makeWin98Font(10.5f, false));
    g.drawText(bypassed ? "Bypassed" : "Ready", sb1.reduced(6, 2), juce::Justification::centredLeft);
    g.drawText(juce::String::formatted("Decimation: 1/%dx Hold", decStep), sb2.reduced(6, 2), juce::Justification::centredLeft);
    g.drawText("Stereo 48.0 kHz", sb3.reduced(6, 2), juce::Justification::centredLeft);
    g.setColour(bypassed ? juce::Colour(160, 0, 0) : juce::Colour(0, 128, 0));
    g.setFont(makeWin98Font(10.5f, true));
    g.drawText(bypassed ? "BYPASS" : "ACTIVE", sb4.reduced(6, 2), juce::Justification::centred);
}

void ProLoFiAudioProcessorEditor::resized() {
    // Toolbar: Presets ComboBox & Bypass Button
    mPresetBox.setBounds(62, 30, 220, 22);
    mBypassButton.setBounds(356, 30, 84, 22);

    // Panel 1: Sampling & Bit-Depth Controls (x=12, y=58, w=430, h=182)
    mSampleRateSlider.setBounds(104, 76, 238, 26);
    mSampleRateLabel.setBounds(352, 78, 80, 22);

    mSampleSizeSlider.setBounds(104, 112, 238, 26);
    mSampleSizeLabel.setBounds(352, 114, 80, 22);

    mAntiAliasSlider.setBounds(104, 148, 238, 26);
    mAntiAliasLabel.setBounds(352, 150, 80, 22);

    mLinearButton.setBounds(142, 192, 90, 22);
    mAdaptiveButton.setBounds(242, 192, 96, 22);

    // Panel 2: Grunge & Color Knobs & Readouts (x=12, y=248, w=430, h=168)
    mDistortionKnob.setBounds(46, 286, 92, 92);
    mDistortionLabel.setBounds(52, 382, 80, 20);

    mNoiseKnob.setBounds(180, 286, 92, 92);
    mNoiseLabel.setBounds(186, 382, 80, 20);

    mSaturationKnob.setBounds(314, 286, 92, 92);
    mSaturationLabel.setBounds(320, 382, 80, 20);
}

} // namespace ProLoFi
