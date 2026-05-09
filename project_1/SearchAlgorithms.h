#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <queue>
#include <set>

using namespace std;

// Prints the given puzzle
void printPuzzle(const vector<vector<int>> &puzzle);

// Peform the actual search given initial state and the algorithm
void generalSearch(const vector<vector<int>> &initial_state,
                    int algorithm_choice);

#endif