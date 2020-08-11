# Audio File PLayer Plugin for JUCE 6 Developers
- Written by Stuart Last
- Published by Spyced Concepts
- Contact hello@spycedconcepts.uk
- Repo: https://github.com/Spyced-Concepts/AudioFilePlayerPlugin


## Acknowledgements
This software has been inspired by the work of Jonathon Racz (https://github.com/jonathonracz/AudioFilePlayerPlugin)
and has been developed in line with Juce 6 bext practice and the guidance of Josh Hodge of The Audio Programmer (https://theaudioprogrammer.com), 

It's definitely worth checking out The Audio Programmer website, Youtube and Discord channels.  I've learned so much about audio programming and love this
vibrant community.

## License
The code and plugin has been released under the GNU V3 Open Source License.  Please ensure that, should you choose to use this code as a basis for your own code, 
that you credit  the author (Stuart Last), the publishing organisation (Spyced Concepts) and link to this Github repo.

Details of the license are included in the [LICENSE.md](LICENSE.md) document.

## Purpose

This VST plugin has been developed for JUCE 6 developers to provide a simple plugin for use in the Juce Plugin Host used for testing.  The plugin simply allows JUCE
developers to open an audio file and use it for testing their own in-development plugins.  If you are using JUCE 5 then Jonathon Racz plugin will work fine (https://github.com/jonathonracz/AudioFilePlayerPlugin).  However, I needed a plugin that was compatible with JUCE 6 and used some of the new JUCE 6 standards.

##  Installation.

Release builds have been included in this repo to make it quick to get started with the plugin.  Navigate tot he builds folder to find compatible builds. 
At this point in time, only Windows machines VSTs are supported because that's all I have access to.  Any Macbook donations most welcome :) .

For Windows - find the AudioFilePlayerPlugin.vst in Builds/VisualStudio2019/x64/Release/VST3/AudioFilePlayerPlugin.vst3 within this repo.

For Mac - You will need to fork/clone this repo, setup JUCER for Mac and build your own version of this plugin using XCODE.  The code for this plugin requires JUCE 6.

Once you have a vst plugin file, place it in your default VST3 x64 directory.  You will then need to open the JUCE Plug-in Host and refresh your list of plugins (or just drag the plugin file across to the open Juce Plugin Host).

##  Usage

This small plugin has been built to be no-frills and very simple to use.  To add an Audio file source to your Juce Plug-in Host, right click in the main area of the host (where all the other plugins are), find "Spyced Concepts" and add the Audio File Player Plugin.

Once loaded you can link the plugin to any other Audio Plugin that requires and audio source.  The path from the Audio File PLayer Plugin will need to end in the native Audio Output plugin.

To open a file, double click on the Audio File Player Plugin and open a file (The filename will be shown at the bottom of the plugin when loaded).  The plugin accepts *.aiff, *.mp3* and *.wav files (there is an inconsistent glitch with *.aif files on Windows machines, but it will accept some of these too).

After that, play and stop to your hearts content.  Stopping playback will reset the transport to 0:0:00.  Playback does not currently loop.

##  Known Issues

1.  There is an inconsistent glitch with the playback of *.aif files which, at this point, has yet to be resolved.
2.  No Mac/Linux friendly version available yet.

## Roadmap (in no particular order)

- Improve look of GUI.
- Add mutiple file "playlist" functionality.
- Add "drag and drop" for audio files,
- Add pause/reset/loop functionality.
- Mac version.
- Linux version.

