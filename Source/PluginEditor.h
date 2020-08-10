/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AudioFilePlayerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AudioFilePlayerPluginAudioProcessorEditor (AudioFilePlayerPluginAudioProcessor&);
    ~AudioFilePlayerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioFilePlayerPluginAudioProcessor& audioProcessor;

    juce::TextButton openButton;
    juce::TextButton playButton;
    juce::TextButton stopButton;

    juce::File audioFile;

    void openButtonClick();
    void playButtonClick();
    void stopButtonClick();

    void addAudioFile(juce::File& file);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioFilePlayerPluginAudioProcessorEditor)
};
