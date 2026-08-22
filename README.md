# Bulls and Cows Algorithmic Solver

A C++ implementation of the Bulls and Cows game, developed for the Algorithms course at the Academic College of Tel-Aviv Yaffo (MTA).

## Features
* **Game Simulation:** Custom n-digit secret numbers with bulls and cows feedback[cite: 1].
* **DFS Strategy:** Finds the lexicographically first consistent guess[cite: 1].
* **BFS Strategy:** Uses a Minimax approach to minimize the worst-case search space depth[cite: 1].

## Usage
Run the program and input the following parameters sequentially when prompted[cite: 1]:
1. `n`: Length of the secret number[cite: 1].
2. `k`: Maximum digit value[cite: 1].
3. `strategy_num`: `1` for DFS, `2` for BFS[cite: 1].
4. `seed`: Random seed for reproducibility[cite: 1].
