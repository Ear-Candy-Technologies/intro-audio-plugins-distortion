#include "PluginProcessor.h"
#include "PluginEditor.h"

DemoDistorAudioProcessorEditor::DemoDistorAudioProcessorEditor (DemoDistorAudioProcessor& p) : AudioProcessorEditor (&p), audioProcessor (p)
{
    /** Input */
    inputSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    inputSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible           (inputSlider);
    inputSlider.setColour       (juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    
    inputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "input", inputSlider);
    
    inputLabel.setText              ("Input", juce::dontSendNotification);
    inputLabel.setJustificationType (juce::Justification::centred);
    inputLabel.attachToComponent    (&inputSlider, false);
    inputLabel.setColour            (juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible               (inputLabel);
    
    /** Gain */
    gainSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible          (gainSlider);
    gainSlider.setColour       (juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    
    gainLabel.setText              ("Gain", juce::dontSendNotification);
    gainLabel.setJustificationType (juce::Justification::centred);
    gainLabel.attachToComponent    (&gainSlider, false);
    gainLabel.setColour            (juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible              (gainLabel);
    
    gainAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "gain", gainSlider);
    
    /** Output */
    outputSlider.setSliderStyle  (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 50, 20);
    addAndMakeVisible            (outputSlider);
    outputSlider.setColour       (juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    
    outputLabel.setText              ("Output", juce::dontSendNotification);
    outputLabel.setJustificationType (juce::Justification::centred);
    outputLabel.attachToComponent    (&outputSlider, false);
    outputLabel.setColour            (juce::Label::ColourIds::textColourId, juce::Colours::black);
    addAndMakeVisible                (outputLabel);
    
    outputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.apvts, "output", outputSlider);
    
    setSize (600, 400);
}

DemoDistorAudioProcessorEditor::~DemoDistorAudioProcessorEditor() {}

void DemoDistorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);
    
    g.drawRoundedRectangle (5, 5, getWidth() - 10, getHeight() - 10, 10, 2);
    
    juce::Rectangle<int> titleRect { 0, 0, getWidth(), (int) (getHeight() * 0.2f) };
    
    g.setFont  (24.0f);
    g.drawText ("Intro distortion", titleRect, juce::Justification::centred);
}

void DemoDistorAudioProcessorEditor::resized()
{
    inputSlider.setBounds  (100, 145, 130, 130);
    gainSlider.setBounds   (240, 145, 130, 130);
    outputSlider.setBounds (370, 145, 130, 130);
}
