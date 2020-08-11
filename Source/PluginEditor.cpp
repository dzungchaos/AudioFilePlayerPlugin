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
    setSize (400,200);

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

    addAndMakeVisible(audioSourceLabel);
    audioSourceLabel.setColour(audioSourceLabel.textColourId, juce::Colours::limegreen);
    audioSourceLabel.setText("Please open a file", juce::NotificationType::dontSendNotification);
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
 
    int lMargin = 20;
    int rMargin = lMargin * 2;
    openButton.setBounds(lMargin, 10, getWidth() - rMargin, 40);
    playButton.setBounds(lMargin, 60, getWidth() - rMargin, 40);
    stopButton.setBounds(lMargin, 110, getWidth() - rMargin, 40);
    audioSourceLabel.setBounds(lMargin, 170, getWidth() - rMargin, 40);
}

void AudioFilePlayerPluginAudioProcessorEditor::openButtonClick()
{
    //open file and add to audioSources
    //Update playlist GUI element
    //if successfull set play button to enabled
    addAudioFile();
    playButton.setEnabled(true);
}

void AudioFilePlayerPluginAudioProcessorEditor::playButtonClick()
{
    audioProcessor.changeState(AudioFilePlayerPluginAudioProcessor::TransportState::Starting);
    openButton.setEnabled(false);
    stopButton.setEnabled(true);
}

void AudioFilePlayerPluginAudioProcessorEditor::stopButtonClick()
{
    audioProcessor.changeState(AudioFilePlayerPluginAudioProcessor::TransportState::Stopping);
    openButton.setEnabled(true);
}

void AudioFilePlayerPluginAudioProcessorEditor::addAudioFile()
{
    juce::FileChooser chooser("Select audio file...", {}, "*.wav; *.mp3; *.aif; *.aiff");
    if (chooser.browseForFileToOpen())
    {
        audioSource = chooser.getResult();
        audioProcessor.loadFile(audioSource);
        juce::String labelText = "Audio File Loaded:  " + audioSource.getFileName();
        audioSourceLabel.setText(labelText, juce::NotificationType::dontSendNotification);
    }
}


