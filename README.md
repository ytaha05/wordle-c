# wordle-c

A simple C implementation of Wordle. Currently bare-bones, but I plan on making the difficulty customizable (allowing for games like Hardle to be played). The game is playable through Unix.

---


## Requirements

- **C Compiler** (e.g., `gcc`, `clang`)
- **Unix-like System** (Linux, macOS, WSL on Windows)
- Terminal or Command Line Interface (CLI)
- **wordle_solutions.txt** and **wordle_guesses.txt** files (included in the repository)

---

## Installation

1. Clone the repository to your local machine (or just download the files):

   ```bash
   git clone https://github.com/ytaha05/wordle-c.git
   cd wordle-c

2. Compile the C code:

   ```bash
   gcc -o wordle wordle.c

3. Run the game:

   ```bash
   ./wordle

## Future plans
  - Add difficulty settings (e.g., allow for "Hardle" with longer words).
  - Implement score tracking and a timer.
  - Allow user to customize word lists or load custom words.
  - Add more comments to my code.



