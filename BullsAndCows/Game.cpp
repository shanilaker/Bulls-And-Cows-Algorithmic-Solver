#include "Game.h"
#include <stdlib.h>
#include <limits>

std::map<int, std::pair<int, int>> Game::my_map;

// Main execution loop for setting up and running the game parameters
void Game::gameRun()
{
    int n = -1, k = -1, strategy_num = -1,secretNumber= -1, seed;
    bool nValidation = true;
    bool kValidation = true;
    bool strategyValidation = true;
    bool invalidInput = false;
    std::string validationString;

    // Input loop for parameter 'n' (typically length of the number)
    
    std::cout << "Enter n: ";
    cin >> validationString;
    std::cout << endl;
    if (!Game::isNumber(validationString)) // Ensure input is numeric
    {
        invalidInput = true;
            
    }
    n = stoi(validationString);
        
    // Validate n is between 1 and 9 inclusive
    nValidation = n < 1 || n > 9;
    if (nValidation)
    {
        invalidInput = true;
    }
    

    // Input loop for parameter 'k' (typically max digit value)
    
    std::cout << "Enter k: ";
    cin >> validationString;
    std::cout << endl;
    if (!Game::isNumber(validationString))
    {
        invalidInput = true;
    }
    k = stoi(validationString);
        
    // Validate k is within range and at least as large as n
    kValidation = k < 1 || k > 9 || k < n;
    if (kValidation)
    {
        invalidInput = true;
    }
    

    // Input loop for strategy selection
    
    std::cout << "Enter strategy_num: ";
    cin >> validationString;
    if (!Game::isNumber(validationString))
    {
        invalidInput = true;
    }
    strategy_num = stoi(validationString);
    std::cout << endl;
    // Validate that strategy_num is either 1 or 2
    strategyValidation = strategy_num != 1 && strategy_num != 2;
    if (strategyValidation)
    {
        invalidInput = true;
    }
    

    // Input loop for random number generator seed
    
    std::cout << "Enter seed: ";
    cin >> validationString;
    if (!Game::isNumber(validationString))
    {
        invalidInput = true;
    }

    if (invalidInput)
    {
        std::cout <<std::endl << "Invalid input" << std::endl;
        exit(1);
    }
    seed = stoi(validationString);
    std::cout << endl;
    
    

    // Generate and display all valid numbers based on n and k parameters
    std::vector<int> possibles = Game::generateAllPossibleNumbers(n, k);
    secretNumber = Game::generateSecretNumber(seed, possibles);

    if (strategy_num == 1)
    {
        Game::DFS(n, k, secretNumber);
    }
    else if (strategy_num == 2)
    {
        Game::BFS(n, k, secretNumber);
    }
    
}

// Validates if a number consists of unique digits between 1 and k
bool Game::isValid(int num, int k) {
    vector<int> usedDigits;

    while (num > 0) {
        int digit = num % 10;
        auto it = std::find(usedDigits.begin(), usedDigits.end(), digit);

        // Check if digit is within allowed range (1 to k) and hasn't been used before (uniqueness)
        if (digit < 1 || digit > k || it != usedDigits.end())
        {
            return false;
        }
        else
        {
            usedDigits.push_back(digit);
        }

        num /= 10;
    }
    return true;
}

// Generates all possible numbers of length n using digits 1 to k
std::vector<int> Game::generateAllPossibleNumbers(int n, int k) {
    std::vector<int> result;

    // Calculate search range (e.g., for n=3, start=100, end=1000)
    int start = 1;
    for (int i = 1; i < n; ++i) start *= 10;
    int end = start * 10;

    // Iterate through range and validate each number
    for (int i = start; i < end; ++i) {
        if (isValid(i, k)) {
            result.push_back(i);
        }
    }

    return result;
}

// Utility to check if a provided string contains only numeric digits
bool Game::isNumber(const std::string& str) {
    if (str.empty()) return false;

    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int Game::generateSecretNumber(int seed, std::vector<int> S)//Generates random number based on seed
{
    mt19937 rng(seed);
    int rand_index = rng() % S.size();

    return S[rand_index];
}

void Game::DFS(int n, int k, int secretNumber)//Main DFS function
{
    bool validGuess = false;
    std::vector<int> possibleNumbers = Game::generateAllPossibleNumbers(n, k);//Gets all possible numbers given n and k
    auto minGuess = std::min_element(possibleNumbers.begin(), possibleNumbers.end(), [](int a, int b) {return std::to_string(a) < std::to_string(b);});
    int minGuessCopy = 0;

    if (minGuess != possibleNumbers.end())
    {
        minGuessCopy = *minGuess;
        possibleNumbers.erase(minGuess);
    }
    while (true)
    {
        Game::checkWithSecretNumber(minGuessCopy, secretNumber);//gets bulls and hits for valid guess
        if (Game::my_map[minGuessCopy].first == n)//checks victory
        {
            Game::printVictory();
            exit(1);
        }
        validGuess = false;
        while (!validGuess) //gets next valid guess
        {
            auto newMinGuess = std::min_element(possibleNumbers.begin(), possibleNumbers.end(), [](int a, int b) {return std::to_string(a) < std::to_string(b);});
            if (newMinGuess != possibleNumbers.end())
            {
                minGuessCopy = *newMinGuess;
                possibleNumbers.erase(newMinGuess);
            }
            validGuess = Game::checkValidGuess(minGuessCopy);

        }
    }
    

}

pair<int ,int> Game::checkBullsAndCows(int guess, int secretNumber)//Counts bulls and cows for a given number
{
    int guessCopy = guess;
    int secretNumberCopy = secretNumber;
    vector<int> guessDigitsArray;
    vector<int> secretDigitsArray;
    int countCows = 0;
    int countBulls = 0;
    int guessDigit;
    int secretDigit;

    while (guessCopy > 0) //adding digits of secret number and guess to arrays, while comparing if in same position (bull)
    {
        guessDigit = guessCopy % 10;
        secretDigit = secretNumberCopy % 10;

        if (secretDigit == guessDigit)
        {
            countBulls++;
        }
        else 
        {
            secretDigitsArray.push_back(secretDigit);
            guessDigitsArray.push_back(guessDigit);
        }

        guessCopy = guessCopy / 10;
        secretNumberCopy = secretNumberCopy / 10;
        
    }

    for (int i = 0; i < secretDigitsArray.size(); i++)//checks non same position numbers if there's a match (checks cows)
    {
        for (int j = 0; j < secretDigitsArray.size(); j++)
        {
            if (guessDigitsArray[i] == secretDigitsArray[j])
            {
                countCows++;
            }
        }
    }
    
    return { countBulls, countCows };
}

void Game::checkWithSecretNumber(int guess, int secretNumber)//gets bulls and cows with the real secret number and adds to guess/feedback map
{
    Game::my_map[guess] = checkBullsAndCows(guess, secretNumber);
}

void Game::printVictory()//Prints our victory once we guess correctly
{
    std::cout << std::endl;
    int roundCount = 1;
    for (const auto& item : Game::my_map) {
        int key = item.first;
        int val1 = item.second.first;
        int val2 = item.second.second;

        std::cout << "Round " << roundCount <<": Guess: " << key << ", Feedback: (" << val1 << ", " << val2 <<  ")" << std::endl;
        roundCount++;
    }
    
    std::cout << std::endl;
    std::cout << "Number of rounds: " << roundCount - 1;

}

bool Game::checkValidGuess(int guess)//Checks if given number is a valid guess 
{
    for (const auto& item : Game::my_map) {
        int key = item.first;
        int val1 = item.second.first;
        int val2 = item.second.second;

        if (checkBullsAndCows(guess, key) != item.second)
        {

            return false;
        }
    }

    return true;
}

std::vector<int> Game::consistentGuessSet(std::vector<int> S, std::pair<int, std::pair<int, int>> guessAndFeedback)//gets set of all consistent guesses
{
    std::vector<int> STag;
    for (const int& item : S)
    {
        if (Game::checkBullsAndCows(item, guessAndFeedback.first) == guessAndFeedback.second)
        {
            STag.push_back(item);
        }
    }
    return STag;//returns vector of all consistent guesses
}

int Game::getMinimalDepthOfSearch(std::vector<int> S)//gets x for which the depth of search is minimal
{
    int minCostNumber = S[0];
    int minCost = Game::getDepthOfSearch(minCostNumber,S);
    

    for (const int& item : S)//going over each x in S and checking if its depth is minimal
    {
        int depthOfSearch = Game::getDepthOfSearch(item,S);
        if (depthOfSearch < minCost)
        {
            minCostNumber = item;
            minCost = depthOfSearch;
        }
    }

    return minCostNumber;
}

int Game::getDepthOfSearch(int guess, std::vector<int> S)//gets the depth of search for given x
{
    // A map to store the size of the set of candidates for each possible feedback
    std::map<std::pair<int, int>, int> feedbackGroups;

    for (const int& secretCandidate : S)
    {
        std::pair<int, int> feedback = Game::checkBullsAndCows(guess, secretCandidate);
        feedbackGroups[feedback]++;
    }

    // Find the feedback that results in the largest remaining set (worst-case)
    int maxSetSize = 0;
    for (std::map<std::pair<int, int>, int>::iterator it = feedbackGroups.begin(); it != feedbackGroups.end(); ++it)
    {
        if (it->second > maxSetSize)
        {
            maxSetSize = it->second;
        }
    }
    return maxSetSize;
}

void Game::BFS(int n, int k, int secretNumber)//Main BFS method
{
    bool validGuess = false;
    // Generate all starting possibilities
    std::vector<int> possibleNumbers = Game::generateAllPossibleNumbers(n, k);
    auto minGuess = std::min_element(possibleNumbers.begin(), possibleNumbers.end(), [](int a, int b) {return std::to_string(a) < std::to_string(b);});
    int minGuessCopy = std::numeric_limits<int>::max();

    // Set the initial guess to the lexicographically smallest item and remove it from the pool
    if (minGuess != possibleNumbers.end())
    {
        minGuessCopy = *minGuess;
        possibleNumbers.erase(minGuess);
    }

    // Main execution loop using the Minimax strategy
    while (true)
    {

        // Score the selected guess
        Game::checkWithSecretNumber(minGuessCopy, secretNumber);
        if (Game::my_map[minGuessCopy].first == n)//Checks victory
        {
            Game::printVictory();
            exit(1);
        }
        else
        {
            // Reduce the search space to only numbers consistent with the new feedback
            possibleNumbers = consistentGuessSet(possibleNumbers, { minGuessCopy, Game::my_map[minGuessCopy] });
            // Choose the next guess
            minGuessCopy = getMinimalDepthOfSearch(possibleNumbers);
        } 
    }
}


