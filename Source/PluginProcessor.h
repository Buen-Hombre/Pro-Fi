#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "DSP/LoFiDSP.h"

namespace ProLoFi {

class ProLoFiAudioProcessor : public juce::AudioProcessor {
public:
    ProLoFiAudioProcessor();
    ~ProLoFiAudioProcessor() override = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Pro-Fi"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    // 25 Factory Presets decoded from Pro Tools Lo-Fi .tfx files
    int getNumPrograms() override;
    int getCurrentProgram() override { return mCurrentPreset; }
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState& getAPVTS() { return mAPVTS; }
    LoFiDSPEngine& getDSPEngine() { return mDSP; }
    const LoFiDSPEngine& getDSPEngine() const { return mDSP; }

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:
    void syncParametersToDSP();

    juce::AudioProcessorValueTreeState mAPVTS;
    LoFiDSPEngine mDSP;
    int mCurrentPreset = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProLoFiAudioProcessor)
};

} // namespace ProLoFi
