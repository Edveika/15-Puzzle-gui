# 15-Puzzle-gui

This project is an extended version of my previous 15 Puzzle CLI project, now featuring a graphical user interface (GUI) built using the SFML library. The 15 Puzzle game is a classic sliding puzzle where the objective is to arrange the tiles in ascending order, leaving an empty space for tile movement.

![Screenshot 2023-08-23 183750](https://github.com/Edveika/15-Puzzle-gui/assets/113787144/59b88690-8232-4805-94da-b8bc777227fa)

## Table of contents

- [New features](#new-features)
- [Original project](#original-cli-project)
- [How to play](#how-to-play)
- [Dependencies](#dependencies)
- [Running the game](#running-the-game)
- [Compiling](#compiling-from-source)
- [License](#license)

## New features

- Arrow key input - move tiles using the arrow keys
- Mouse input - move tiles by clicking on them with the mouse
- GUI - CLI replaced with SFML

## Original CLI Project

For the original 15 Puzzle CLI project, you can visit [here](https://github.com/Edveika/15-Puzzle-cli).

## How to Play

- Use mouse clicks or keyboard arrows/WASD to move tiles and arrange them in order.
- The game is won when tiles are in ascending order, from top-left to bottom-right, with an empty space at the bottom-right corner.

## Dependencies

- SFML (Simple and Fast Multimedia Library): Required for graphical rendering and input handling.

NOTE: this is needed for those who want to compile, if you want to run the game see [Running the game](#running-the-game)

## Running the game

1. Download the game from [releases](https://github.com/Edveika/15-Puzzle-gui/releases/tag/1.0)
2. Extract 15-Puzzle-gui.zip file
3. Run the exe from the extracted folder

## Compiling from source

1. Make sure you have SFML installed. You can download it from [here](https://www.sfml-dev.org/).
2. Clone this repository.
3. Include SFML library to the project(Include and Lib, tutorial [here](https://www.sfml-dev.org/tutorials/2.6/start-vc.php))
4. Compile the source files using Visual Studio or your preferred IDE.

## License

This project is licensed under the GPL v2 [LICENSE](LICENSE).

_Enjoy the challenge of solving the 15 Puzzle!_
