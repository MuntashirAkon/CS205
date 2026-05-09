#include "SearchAlgorithms.h"
#include <iostream>
#include <vector>

using namespace std;

// Returns the default puzzle
vector<vector<int>> getDefaultPuzzle();

// Takes puzzle as input from the user
vector<vector<int>> getCustomPuzzle();

int main() {
  cout << "Muntashir's N-Puzzle Solver." << endl;

  int choice;

  vector<vector<int>> puzzle;
  while (true) {
    // Ask which puzzle to use
    cout << "Type '1' to use a default puzzle, or '2' to enter your own."
         << endl;
    cin >> choice;

    if (choice == 1 || choice == 2) {
      // Valid choice
      break;
    }
    cout << "Invalid choice. Please try again." << endl;
    // Continue asking until the user gets it right
  }

  if (choice == 1) {
    puzzle = getDefaultPuzzle();
    cout << "Using the default 3x3 puzzle:" << endl;
  } else if (choice == 2) {
    puzzle = getCustomPuzzle();
    cout << "Your puzzle:" << endl;
  }

  // Print the puzzle we got from the user
  printPuzzle(puzzle);

  while (true) {
    // Ask which algorithm to use
    cout << "Select algorithm." << endl;
    cout << "1. Uniform Cost Search" << endl;
    cout << "2. A* with Misplaced Tile Heuristic" << endl;
    cout << "3. A* with Manhattan Distance Heuristic." << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1 || choice == 2 || choice == 3) {
      // Valid choice
      break;
    }
    cout << "Invalid choice. Please try again." << endl;
    // Continue asking until the user gets it right
  }

  // Solve the puzzle
  generalSearch(puzzle, choice);

  return 0;
}

vector<vector<int>> getDefaultPuzzle() {
  // Generated from here: https://deniz.co/8-puzzle-solver/
  return {{0, 1, 5}, {3, 6, 2}, {4, 7, 8}};
}

vector<vector<int>> getCustomPuzzle() {
  cout << "Enter grid size: " << endl;
  int grid_size;
  cin >> grid_size;

  cout << "Enter your puzzle." << endl;
  cout << "Use 0 to denote the blank. Use space to separate items in each row."
          "Size of each row must match. Press enter when done with the row."
       << endl;

  vector<vector<int>> customPuzzle(grid_size, vector<int>(grid_size));

  for (int row = 0; row < grid_size; row++) {
    cout << "Row " << (row + 1) << ": ";
    for (int col = 0; col < grid_size; col++) {
      cin >> customPuzzle[row][col];
    }
  }

  return customPuzzle;
}
