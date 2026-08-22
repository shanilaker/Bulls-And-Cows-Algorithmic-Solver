# Bulls and Cows Solver 🎯

This is a C++ implementation of the classic Bulls and Cows code-breaking game. Not only does it simulate the game, but it also includes two automated algorithmic strategies to crack the secret number as efficiently as possible.

## How It Works
The program generates a secret number, and the built-in solvers try to guess it using feedback (Bulls = right digit, right place; Cows = right digit, wrong place). 

* **DFS Strategy:** A straightforward approach that iterates through the options and picks the first guess that perfectly aligns with all previous feedback.
* **BFS (Minimax) Strategy:** A more advanced approach that evaluates the search space to minimize the worst-case scenario, guaranteeing it finds the secret number in the fewest possible rounds.

## Getting Started
When you run the compiled program, the console will ask you for four setup parameters:
1. `n`: The length of the secret number.
2. `k`: The maximum digit value allowed.
3. `strategy_num`: Type `1` for the DFS solver or `2` for the BFS solver.
4. `seed`: A random seed number so you can replay the exact same game setup.
