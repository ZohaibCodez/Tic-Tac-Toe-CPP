# 🕹️ Tic Tac Toe in C++

A simple command-line Tic Tac Toe game written in C++ with multiple game modes and computer AI strategies.

## 🎮 Features

* **4 Game Modes:**

  1. Human vs Human
  2. Human vs Nonsense Computer (random moves)
  3. Human vs Sensible Computer (basic strategy)
  4. Nonsense Computer vs Sensible Computer

* **Two AI Players:**

  * **NonsenseComputerPlayer:** chooses random empty cells.
  * **SensibleComputerPlayer:** tries to win, block the opponent, or create future winning opportunities.

* **Board Display:** Clean console-based 3x3 board.

* **Input Validation:** Ensures valid mark and box choices.

* **Replay Option:** Play again without restarting the program.

## 🛠️ How It Works

The game uses object-oriented design:

* `Player` is an abstract base class.
* `HPlayer` (human), `NonSenseComputerPlayer`, and `SensibleComputerPlayer` are derived classes.
* `Board` manages board state and drawing.
* `Game` class coordinates the entire gameplay loop.

## 🧠 Sensible AI Strategy

The **SensibleComputerPlayer** evaluates the board in this order:

1. **Win:** If it can win in this move, it does.
2. **Block:** If the opponent can win next, it blocks.
3. **Opportunity:** If it can create a future win (1 in a line), it tries.
4. **Fallback:** Otherwise, it picks a random empty cell.

## 🚀 Getting Started

### 🧾 Prerequisites

* A C++ compiler (e.g., `g++`, `clang++`, or MSVC)

### 🔧 Build Instructions

Open a terminal and compile with:

```bash
g++ TicTacToeTask.cpp -o TicTacToe
```

Run the game:

```bash
./TicTacToe     # on Linux or Mac
TicTacToe.exe   # on Windows
```

## 🖥️ Example Gameplay

```text
==== TIC TAC TOE ====
Select game mode:
1: Human vs Human
2: Human vs Nonsense Computer
3: Human vs Sensible Computer
4: Nonsense Computer vs Sensible Computer
Enter your choice (1-4): 3
Choose mark for Player 1 (O/X): X
Game Mode: Human vs Sensible Computer

 ___ ___ ___ 
|   |   |   |
| 1 | 2 | 3 |
|___|___|___|
|   |   |   |
| 4 | 5 | 6 |
|___|___|___|
|   |   |   |
| 7 | 8 | 9 |
|___|___|___|
```

## 📂 File Structure

```
TicTacToeTask.cpp    # Main source file containing all game classes
README.md            # This documentation file
```

## ✍️ Author

* Created as part of an OOP lab project using C++.
* Developed by Zohaib Khan.

## 📜 License

This project is open-source and free to use. Attribution appreciated!

