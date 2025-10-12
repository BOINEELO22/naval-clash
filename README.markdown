# Naval Clash

Naval Clash is a console-based C++ implementation of a simplified Battleship game. Players can compete in two modes: Player vs. Player or Player vs. Computer. Each player has a 4x4 grid with randomly placed ships, and the goal is to sink the opponent's ships by guessing their locations. The game saves grid states to text files during play and can display final grids at the end.

## Features
- **Two Game Modes**:
  - Player vs. Player: Two human players take turns guessing.
  - Player vs. Computer: One human player competes against a computer with random guesses.
- **4x4 Grid**: Each player’s grid has 4 ships ('S'), one per row, randomly placed.
- **Turn-Based Gameplay**: Players guess cells (1–16) to attack, marking hits ('H') or misses ('X'). Each player has 5 chances.
- **Progress Tracking**: Grids are saved to `player1_grid.txt` (Player 2’s grid) and `player2_grid.txt` (Player 1’s grid) during gameplay.
- **Final Grid Display**: Optionally view final grids (`player1_final_grid.txt`, `player2_final_grid.txt`) showing ships ('S'), hits ('H'), misses ('X'), and water ('~').
- **Score Display**: Shows ships destroyed and declares a winner based on the highest score.
- **Replay Option**: Play multiple rounds, resetting grids and computer guesses each game.

## Game Rules
- Each player has a 4x4 grid with 4 ships ('S'), one randomly placed in each row.
- Players take turns guessing a cell (1–16) on the opponent’s grid, with 5 chances each.
- A guess results in:
  - **Hit ('H')**: The cell contains a ship.
  - **Miss ('X')**: The cell is empty (water, '~').
- The game ends when one player destroys all 4 opponent ships or both use all 5 chances.
- The player with more ships destroyed wins. If equal, it’s a draw.
- After the game, choose to view final grids (saved to files) or skip.

## Installation
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/naval-clash.git
   cd naval-clash
   ```
2. **Compile the Code**:
   Use a C++ compiler (e.g., g++):
   ```bash
   g++ -o naval_clash main.cpp
   ```
3. **Run the Game**:
   ```bash
   ./naval_clash
   ```
   On Windows:
   ```bash
   naval_clash.exe
   ```

## Usage
1. Start the game to see: `WELCOME TO NAVAL CLASH`.
2. Choose a mode:
   - `1`: Player vs. Player (enter names for both players).
   - `2`: Player vs. Computer (enter your name; computer is named “COMPUTER”).
3. Gameplay:
   - View the opponent’s grid (shows numbers 1–16 for untargeted cells, 'H' for hits, 'X' for misses).
   - Enter a number (1–16) to guess a cell. In Player vs. Computer mode, the computer guesses randomly.
   - Feedback shows “HIT!!! SHIP DESTROYED!!!” or “MISS!!!”.
4. Game End:
   - Scores display the number of ships destroyed and the winner.
   - Choose `Y`/`y` to view final grids (saved to files) or `N`/`n` to skip.
   - Choose `Y`/`y` to play again or `N`/`n` to exit.

## File Structure
```
naval-clash/
├── game.cpp              # Source code for the game
├── .gitignore            # Specifies files to ignore (e.g., compiled outputs)
├── README.md             # This documentation
```

## Dependencies
- **C++ Standard Library**: Uses `<iostream>`, `<fstream>`, `<ctime>`, `<cstdlib>`, `<random>`, `<iomanip>`, `<limits>`, `<string>`, `<vector>`, `<thread>`, `<chrono>`.
- **C++11 or later**: Required for `std::thread` and `std::chrono`.
- A C++ compiler (e.g., g++, clang++, MSVC).

No external libraries are required.

## Notes
- Grid files (`player1_grid.txt`, etc.) are generated during gameplay and ignored by `.gitignore` to keep the repository clean.
- If file operations fail (e.g., due to permissions), an error message (“Error opening file!”) is displayed, and final grids may not show.
- The computer’s guesses in Player vs. Computer mode are random but avoid previously selected cells within a game.

## Author
Boineelo Mothibedi

## License
This project is released under the **MIT License**. You are free to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of this software, provided that you include the copyright notice and this permission notice in all copies or substantial portions of the Software.

A copy of the full license text is provided in the repository as `LICENSE`.
