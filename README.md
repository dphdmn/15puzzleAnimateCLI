## 15puzzleAnimateCLI - Animation Tool for Windows CMD (C++)

15puzzleAnimateCLI is a specialized animation tool developed for the Windows Command Prompt (CMD) using C++. With a focus on simplicity and efficiency, this tool allows you to create captivating animations of the 15 Puzzle concept within the Windows CMD window.

**Please Note:** The animations created with 15puzzleAnimateCLI are designed to be displayed solely within the Windows Command Prompt (CMD) environment and do not generate any standalone animation files.

### Requirements

Before using 15puzzleAnimateCLI, make sure to have the "slidycli" library installed. You can find the library and installation instructions at [slidy-cli](https://github.com/benwh1/slidy-cli/releases).

### Usage

Follow these steps to create your 15 Puzzle animations:

1. Clone or download the repository to your local machine.

2. Compile the tool by running `compile.bat` from `colortest.cpp`, or simply download `core.exe` if you prefer the precompiled version.

3. Now, you can create an animation using the following example command:

   ```
   animate "10 7 6 11/1 3 12 5/4 13 14 2/9 0 15 8" "DLDLDRRUURULLDRDLULDDRRRULDLUULURRDDLLDRRULLUU"
   ```

   This command will animate the 15 Puzzle with the initial configuration `10 7 6 11/1 3 12 5/4 13 14 2/9 0 15 8`, following the sequence of movements provided in the second argument `DLDLDRRUURULLDRDLULDDRRRULDLUULURRDDLLDRRULLUU`.

   Ensure that the input format for the 15 Puzzle configuration is correct, with numbers separated by spaces, and each row separated by a forward slash. The movement sequence should consist of characters 'U' (up), 'D' (down), 'L' (left), and 'R' (right) to represent the sliding direction of the tile.

### Creating 15 Puzzle Animations

The 15 Puzzle Animation Tool lets you craft animations based on the classic 15 Puzzle concept. It enables you to animate the sliding of numbered tiles on a 4x4 grid directly within the Windows Command Prompt.

Key Features:
- Simple Interface: Enjoy a user-friendly interface for creating 15 Puzzle animations without unnecessary complexities.
- CMD-based Animation: Utilize the convenience of creating animations directly within the Windows Command Prompt environment.
- Powered by "slidycli": Leverage the capabilities of the "slidycli" library to produce smooth and captivating animations.

### Get Started

Explore the possibilities of animation with 15puzzleAnimateCLI! Create interactive sliding tile sequences and bring your ideas to life within the Windows Command Prompt.

*Note: For any issues or suggestions, please feel free to contribute to the project on GitHub.*

Embark on your animation journey with 15puzzleAnimateCLI! 🚀🎞️
