/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioFilePlayerPluginAudioProcessor::AudioFilePlayerPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
}

AudioFilePlayerPluginAudioProcessor::~AudioFilePlayerPluginAudioProcessor()
{
}

//==============================================================================
const juce::String AudioFilePlayerPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AudioFilePlayerPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AudioFilePlayerPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AudioFilePlayerPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AudioFilePlayerPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AudioFilePlayerPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AudioFilePlayerPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AudioFilePlayerPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AudioFilePlayerPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void AudioFilePlayerPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AudioFilePlayerPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    transportSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void AudioFilePlayerPluginAudioProcessor::releaseResources()
{
    transportSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AudioFilePlayerPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
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

void AudioFilePlayerPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    transportSource.getNextAudioBlock(juce::AudioSourceChannelInfo(buffer));
}

//==============================================================================
bool AudioFilePlayerPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AudioFilePlayerPluginAudioProcessor::createEditor()
{
    return new AudioFilePlayerPluginAudioProcessorEditor (*this);
}

//==============================================================================
void AudioFilePlayerPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AudioFilePlayerPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void AudioFilePlayerPluginAudioProcessor::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;
        switch (state)
        {
            case Stopped:
                transportSource.setPosition(0.0);
                break;
            case Starting:
                transportSource.start();
                break;
            case Stopping:
                transportSource.stop();
                break;
        }
    }
}

void AudioFilePlayerPluginAudioProcessor::loadFile(juce::File &filename)
{
    auto* reader = formatManager.createReaderFor(filename);

    if (reader != nullptr)
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void AudioFilePlayerPluginAudioProcessor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
        {
            changeState(Playing);
        }
        else
        {
            changeState(Stopped);
        }

    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioFilePlayerPluginAudioProcessor();
}
