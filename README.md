# Beat Saber Song Splitter

A tool for splitting long songs into smaller segments for charting in Beat Saber.

## Description

BSSS Is a tool designed for charting very long songs in Beat Saber using [EditSaber](https://github.com/Ikeiwa/EditSaber). It allows you to create shorter segments throughout the song to make playtesting later parts easier, as well as to eliminate lag that comes from loading long songs into EditSaber.

## Requirements

### To compile

[JSON for Modern C++](https://nlohmann.github.io/json/) by nlohmann ([GitHub Link](https://github.com/nlohmann/json))

### To run

**FFmpeg**

[FFmpeg](https://www.ffmpeg.org/) is required, but a copy of the needed files is included with [official releases](https://github.com/Isvvc/Beat-Saber-Song-Splitter/releases).

The current Batchfiles are hard-coded to support ffmpeg-4.0-win64-static, though that is arbitrary and essentially any version of FFmpeg should work.

## Usage

### Setup

1. Create a new song in EditSaber (BSSS does not currently support modifying existing songs) and create an Expert difficulty (only Expert is supported at this time).
1. Download the latest release and place all files, including the compiled `.exe` file, into the folder for the song you are charting.
1. Create arbitrarily named subfolders in the song folder for the different segments.
1. In each subfolder, create a file called `meta.txt`. On the first line place the time, in seconds, that you want that segment to start. On the second line, place the time, in seconds, that you want the segment to end.
1. Drag the `.ogg` audio file for your song onto `split.bat`. This will generate split audio segments based on your specifications in the folders' `meta.txt` files and will place the necessary files in each folder.

### Charting

1. Go into the folder of the segment you want to chart and run `Set as active.bat` (not the one in the top-level song folder).
1. Chart the segment in EditSaber and playtest in Beat Saber.
1. Once your segment is charted and saved in EditSaber, close EditSaber or go to the song selection screen (don't stay on the song infos and difficulties screen) and run `Save current segment.bat`. This will save the `Expert.json` file into the folder for the segment you had activated.
1. Repeat for each segment.
1. When all segments are completed (or when you want to test the segments together), drag the `.ogg` audio file for your song onto `merge.bat` to have all of the segments merged into one, ready to be played in Beat Saber.
