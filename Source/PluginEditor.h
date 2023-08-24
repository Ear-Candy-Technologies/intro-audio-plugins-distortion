#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class DemoDistorAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    
    DemoDistorAudioProcessorEditor (DemoDistorAudioProcessor&);
    ~DemoDistorAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    DemoDistorAudioProcessor& audioProcessor;
    
    juce::Slider inputSlider;
    juce::Slider gainSlider;
    juce::Slider outputSlider;
    
    juce::Label inputLabel;
    juce::Label gainLabel;
    juce::Label outputLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> inputAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttach;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoDistorAudioProcessorEditor)
};
