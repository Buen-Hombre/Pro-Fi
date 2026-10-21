#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace ProLoFi {

ProLoFiAudioProcessor::ProLoFiAudioProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input",   juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      mAPVTS(*this, nullptr, "ProLoFiParameters", createParameterLayout())
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ProLoFiAudioProcessor::createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // 1. Sample Rate (normalized 0.0..1.0, 63 discrete steps, LoFi.xml interval=0.016)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ "SampleRate", 1 },
        "Sample Rate",
        juce::NormalisableRange<float>(0.0f, 1.0f, 1.0f / 63.0f),
        1.0f
    ));

    // 2. Anti-Alias (0..100%, LoFi.xml interval=0.01)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ "AntiAlias", 1 },
        "Anti-Alias",
        juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f),
        100.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
    ));

    // 3. Sample Size (2..24 bits, __const @ 0x124708 = {2, 24})
    params.push_back(std::make_unique<juce::AudioParameterInt>(
        juce::ParameterID{ "SampleSize", 1 },
        "Sample Size",
        2, 24, 24,
        juce::AudioParameterIntAttributes().withLabel("bits")
    ));

    // 4. Quantization (0 = Linear, 1 = Adaptive)
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
        juce::ParameterID{ "Quantization", 1 },
        "Quantization",
        juce::StringArray{ "Linear", "Adaptive" },
        0
    ));

    // 5. Noise (0.0..100.0%, LoFi.xml BigKnob)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ "Noise", 1 },
        "Noise",
        juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f),
        0.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")
    ));

    // 6. Distortion (0.0..10.0, LoFi.xml SmallKnob)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ "Distortion", 1 },
        "Distortion",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.1f),
        0.0f
    ));

    // 7. Saturation (0.0..10.0, LoFi.xml SmallKnob)
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{ "Saturation", 1 },
        "Saturation",
        juce::NormalisableRange<float>(0.0f, 10.0f, 0.1f),
        0.0f
    ));

    // 8. Master Bypass
    params.push_back(std::make_unique<juce::AudioParameterBool>(
        juce::ParameterID{ "Bypass", 1 },
        "Master Bypass",
        false
    ));

    return { params.begin(), params.end() };
}

void ProLoFiAudioProcessor::prepareToPlay(double sampleRate, int /*samplesPerBlock*/) {
    mDSP.prepare(sampleRate);
    syncParametersToDSP();
}

void ProLoFiAudioProcessor::releaseResources() {
    mDSP.reset();
}

bool ProLoFiAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    const auto& mainIn  = layouts.getMainInputChannelSet();
    const auto& mainOut = layouts.getMainOutputChannelSet();
    if (mainIn != mainOut) return false;
    return (mainOut == juce::AudioChannelSet::mono()
         || mainOut == juce::AudioChannelSet::stereo());
}

void ProLoFiAudioProcessor::syncParametersToDSP() {
    const bool   bypass     = mAPVTS.getRawParameterValue("Bypass")->load() >= 0.5f;
    const double srNorm     = mAPVTS.getRawParameterValue("SampleRate")->load();
    const double antiAlias  = mAPVTS.getRawParameterValue("AntiAlias")->load();
    const int    sampleSize = static_cast<int>(std::round(mAPVTS.getRawParameterValue("SampleSize")->load()));
    const int    quantMode  = static_cast<int>(std::round(mAPVTS.getRawParameterValue("Quantization")->load()));
    const double noise      = mAPVTS.getRawParameterValue("Noise")->load();
    const double distortion = mAPVTS.getRawParameterValue("Distortion")->load();
    const double saturation = mAPVTS.getRawParameterValue("Saturation")->load();

    mDSP.updateParameters(bypass, srNorm, antiAlias, sampleSize, quantMode, noise, distortion, saturation);
}

void ProLoFiAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/) {
    juce::ScopedNoDenormals noDenormals;

    syncParametersToDSP();

    const int numChannels = buffer.getNumChannels();
    const int numSamples  = buffer.getNumSamples();

    mDSP.processBlock(buffer.getArrayOfReadPointers(),
                      buffer.getArrayOfWritePointers(),
                      numChannels,
                      numSamples);
}

int ProLoFiAudioProcessor::getNumPrograms() {
    return 25;
}

const juce::String ProLoFiAudioProcessor::getProgramName(int index) {
    if (index >= 0 && index < 25) {
        return AAX_Original::kFactoryPresets[index].name;
    }
    return {};
}

void ProLoFiAudioProcessor::setCurrentProgram(int index) {
    if (index < 0 || index >= 25) return;
    mCurrentPreset = index;
    const auto& p = AAX_Original::kFactoryPresets[index];

    if (auto* param = mAPVTS.getParameter("SampleRate"))
        param->setValueNotifyingHost(param->convertTo0to1(p.sampleRateNorm));
    if (auto* param = mAPVTS.getParameter("AntiAlias"))
        param->setValueNotifyingHost(param->convertTo0to1(p.antiAliasPct));
    if (auto* param = mAPVTS.getParameter("SampleSize"))
        param->setValueNotifyingHost(param->convertTo0to1(static_cast<float>(p.sampleSizeBits)));
    if (auto* param = mAPVTS.getParameter("Quantization"))
        param->setValueNotifyingHost(param->convertTo0to1(static_cast<float>(p.quantization)));
    if (auto* param = mAPVTS.getParameter("Noise"))
        param->setValueNotifyingHost(param->convertTo0to1(p.noisePct));
    if (auto* param = mAPVTS.getParameter("Distortion"))
        param->setValueNotifyingHost(param->convertTo0to1(p.distortion));
    if (auto* param = mAPVTS.getParameter("Saturation"))
        param->setValueNotifyingHost(param->convertTo0to1(p.saturation));
}

void ProLoFiAudioProcessor::changeProgramName(int /*index*/, const juce::String& /*newName*/) {}

void ProLoFiAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto state = mAPVTS.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ProLoFiAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(mAPVTS.state.getType())) {
        mAPVTS.replaceState(juce::ValueTree::fromXml(*xmlState));
    }
}

juce::AudioProcessorEditor* ProLoFiAudioProcessor::createEditor() {
    return new ProLoFiAudioProcessorEditor(*this);
}

} // namespace ProLoFi

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new ProLoFi::ProLoFiAudioProcessor();
}
