#include "PluginProcessor.h"
#include "PluginEditor.h"

DemoDistorAudioProcessor::DemoDistorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

DemoDistorAudioProcessor::~DemoDistorAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout DemoDistorAudioProcessor::createParameters()
{
    // Esto es un comentario
    // juce::ParameterID("nombre", 1), "nombre", inicio.f, fin.f, default.f)
    juce::AudioProcessorValueTreeState::ParameterLayout params;
    
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("input",1), "input", 0.0f, 2.0f, 1.0f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("gain",1), "gain", 0.0f, 3.0f, 1.5f));
    params.add(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("output",1), "output", 0.0f, 2.0f, 1.0f));

    return params;
    
}

const juce::String DemoDistorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DemoDistorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DemoDistorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DemoDistorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DemoDistorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DemoDistorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DemoDistorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DemoDistorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DemoDistorAudioProcessor::getProgramName (int index)
{
    return {};
}

void DemoDistorAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

void DemoDistorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DemoDistorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DemoDistorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DemoDistorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    // Obtengo Parametros del usuario
    float inputValue  = *apvts.getRawParameterValue ("input");
    float gainValue   = *apvts.getRawParameterValue ("gain");
    float outputValue = *apvts.getRawParameterValue ("output");
    
    // Inicio procesamiento
    for (int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            // Obtengo la muestra de mi buffer en el canal actual
            float inSample = buffer.getSample(channel, i);
            
            // Procesamiento DSP
            // Input
            float outSample = inSample * inputValue;
            //Distortion
            outSample = outSample * gainValue;
            outSample = outSample - (powf(outSample, 3.0f)/3.0f);
            
            // Output
            outSample = outSample * outputValue;
            
            // Setear nuevo valor de muestra en el buffer
            buffer.setSample(channel, i, outSample);
        }
    }
}

//==============================================================================
bool DemoDistorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DemoDistorAudioProcessor::createEditor()
{
    return new DemoDistorAudioProcessorEditor (*this);
    //return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void DemoDistorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DemoDistorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DemoDistorAudioProcessor();
}
