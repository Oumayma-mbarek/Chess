# Chess Game Project in C++ ♚

**Author:** Oumayma MBAREK
*I affirm that this is my own personal work.*

---

## 🧠 Project Overview

This project was implemented as part of the object oriented programming class in  [**Telecom Physique Strasbourg**](https://www.telecom-physique.fr/) engineering school 

This project is a simplified implementation of a chess game in C++. It includes the creation and management of the game board, pieces, and movement logic. The main design is object-oriented, with classes representing the board, pieces, and game control flow. The most challenging part was the initial development, especially building the display logic and managing how to represent and manipulate the board state. I also struggled with deciding which methods should belong to which class, especially early on. Debugging segmentation faults was also a major difficulty, especially when dealing with pointers and class interactions.

---

## ⚙️ How to Compile and Run
### 1 ─ Download dependencies and Install

- If G++ is not installed on your computer, run these commands, as the `makefile` requires G++ as the compiler.

```bash
$ sudo apt update
$ sudo apt install build-essential
$ sudo apt install g++
```

- Clone the repository with git

### 2 ─ Use Makefile

Compile the program run the following command :

```bash
$ make
```

### 3 ─ Run the program
To begin a game, run the following command :
```bash
$ ./echecs
```
### 4 ─ Documentation 
You can use [Doxygen](https://www.doxygen.nl/) to generate documentation.

To install doxygen, run :
```bash
$ sudo apt install doxygen
```

To generate documentation, use the following command :

```bash
$ make doc
xdg-open html/index.html
```

PDF documentation is also available via:
```bash 
make pdf
xdg-open docs/latex/refman.pdf
```

Then open `documentation/html/index.html` in your browser

## ♟️ How the Game Works

This is a two-player command-line chess game. Players take turns entering moves using standard chess notation (e.g., `e2e4`). The game enforces the official rules of chess, including valid movement for each piece, alternating turns, and special moves. The game ends when a player resigns, a draw is declared, or a checkmate or stalemate occurs.

### Key Rules Implemented

- **Checkmate**: Occurs when a player is in check and has no legal moves to escape. The game ends, and the opponent wins.
- **Stalemate**: Happens when a player is **not in check** but has **no legal moves** left. This results in a draw.
- **En Passant**: A special pawn capture that can occur if a pawn moves two squares forward from its starting position and lands beside an opponent's pawn. On the next turn only, the opponent can capture it as if it had moved one square forward.


## ✅ Unit Tests
All unit tests were executed using test-level.sh, and all tests passed successfully.

No failing tests to report

## 📄 Additional Notes
The program was tested and developed on Arch Linux using g++ and make.




