/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioFilePlayerPluginAudioProcessorEditor::AudioFilePlayerPluginAudioProcessorEditor (AudioFilePlayerPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    addAndMakeVisible(openButton);
    openButton.onClick = [this] { openButtonClick(); };
    openButton.setColour(openButton.buttonColourId, juce::Colours::blue);
    openButton.setButtonText("Open Audio File");

    addAndMakeVisible(playButton);
    playButton.onClick = [this] { playButtonClick(); };
    playButton.setColour(playButton.buttonColourId, juce::Colours::darkgreen);
    playButton.setButtonText("Play Audio");
    playButton.setEnabled(false);

    addAndMakeVisible(stopButton);
    stopButton.onClick = [this] {stopButtonClick(); };
    stopButton.setColour(stopButton.buttonColourId, juce::Colours::maroon);
    stopButton.setButtonText("Stop Playback");
    stopButton.setEnabled(false);
}

AudioFilePlayerPluginAudioProcessorEditor::~AudioFilePlayerPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioFilePlayerPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

 
}

void AudioFilePlayerPluginAudioProcessorEditor::resized()
{
    int margin = 20;
    openButton.setBounds(margin, 10, getWidth() - margin, 40);
    playButton.setBounds(margin, 60, getWidth() - margin, 40);
    stopButton.setBounds(margin, 110, getWidth() - margin, 40);
}

void AudioFilePlayerPluginAudioProcessorEditor::openButtonClick()
{
    playButton.setEnabled(true);
    stopButton.setEnabled(true);
    
}

void AudioFilePlayerPluginAudioProcessorEditor::playButtonClick()
{
    openButton.setEnabled(false);
}

void AudioFilePlayerPluginAudioProcessorEditor::stopButtonClick()
{
    openButton.setEnabled(true);
}
