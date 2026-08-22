#include "Game.h"


/*
 * ======================================================================================
 * BULLS AND COWS SOLVER - OPERATING INSTRUCTIONS
 * ======================================================================================
 * Upon running the program, follow these prompts sequentially in the console:
 * * 1. Enter n: The length of the secret number (integer between 1 and 9).
 * 2. Enter k: The maximum digit value used (integer between 1 and 9, must be >= n).
 * 3. Enter strategy_num:
 * - Enter '1' for DFS (Depth-First Search) strategy.
 * - Enter '2' for BFS (Breadth-First Search) strategy.
 * 4. Enter seed: A numeric seed for the random number generator to select the secret number.
 * * The program will then perform the chosen strategy
 * to guess it, outputting the results round-by-round until victory.
 * ======================================================================================
 */

int main()
{
	Game::gameRun();
	return 0;
}