
# Basic Auto Pets

This repository contains a basic C++ implementation of the core concept of the game [SuperAutoPets](https://store.steampowered.com/app/1714040/Super_Auto_Pets/), with a simple CLI interface.


## Installation

The code needs the following libraries to compile:
- C++20 compiler
- ncursesw

To compile, simply clone the directory and run `make`.


## Enemy teams

The enemy teams are sampled uniformly from the list of teams saved in `data/saved_teams.txt` (respecting the current turn number).
A team is represented using the format :
`turn_number (Name1 Attack1 Life1 XP1 Status1) (Name2 Attack2 Life2 XP2 Status2) ...`

This file can simply be modified by hand, or generated using automatic tools.
A team extractor using videos of streamers can be found on https://github.com/Val95240/SAPTeamExtractor .

