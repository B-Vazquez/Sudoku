# Sudoku Solver

This project reads a 16x16 hexadecimal Sudoku puzzle from `puzzle.txt`, validates the board structure, and then searches for every valid solution using backtracking.

## What the program does

- Reads a puzzle from a text file.
- Accepts values `0` through `9` and `a` through `f`.
- Uses `.` to represent a blank cell.
- Writes all discovered solutions to `solution.txt`.

## File roles

- `Project3-Sudoku/VazquezProject3.cpp` — program entry point that opens the input and output files and starts the solving process.
- `Project3-Sudoku/Sudoku.h` — class declaration for the solver.
- `Project3-Sudoku/Sudoku.cpp` — puzzle loading, validation, and recursive solving logic.
- `puzzle.txt` — sample puzzle input.
- `solution.txt` — output file generated when the program runs.

## Build and run

From the workspace root, compile and run the project with your preferred C++ toolchain. In Visual Studio Code, the provided solution can be used to build and run the project.

Important runtime note:
- The program expects `puzzle.txt` to exist in the working directory where the executable is launched.
- When running from the Visual Studio solution, keep the input file in the same folder as the project or adjust the working directory accordingly.

## Input assumptions

The puzzle must be a 16x16 grid with exactly 16 characters per line. Each character must be either:
- a hexadecimal digit (`0`-`9`, `a`-`f`), or
- `.` for a blank cell.

The program currently assumes the file follows this format and will report an error if the structure is malformed or contains duplicate values that violate Sudoku constraints.

## Known limitations

- The program is designed for the specific 16x16 hexadecimal Sudoku format used in this project.