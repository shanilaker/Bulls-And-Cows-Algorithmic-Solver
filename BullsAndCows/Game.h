#pragma once
#include <random>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Game
{
	static std::map<int, std::pair<int, int>> my_map;

	static std::vector<int> generateAllPossibleNumbers(int n, int k);
	static int getMinimalDepthOfSearch(std::vector<int> S);
	static int generateSecretNumber(int seed, std::vector<int> S);
	static int getDepthOfSearch(int guess, std::vector<int> S);
	static bool checkValidGuess(int guess);
	static bool isValid(int num, int k);
	static bool isNumber(const std::string& str);
	static void checkWithSecretNumber(int guess, int secretNumber);
	static void DFS(int n, int k, int secretNumber);
	static void BFS(int n, int k, int secretNumber);
	static void printVictory();
	static std::vector<int> consistentGuessSet(std::vector<int> S, std::pair<int, std::pair<int, int>> guessAndFeedback);
	static pair<int, int> checkBullsAndCows(int guess, int secretNumber);
	

	public: 
		static void gameRun();
};

