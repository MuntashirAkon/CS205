#include <iostream>
#include <vector>

using namespace std;

// Prints the given puzzle
void printPuzzle(const vector<vector<int>> &puzzle);

// Returns the default puzzle
vector<vector<int>> getDefaultPuzzle();

// Takes puzzle as input from the user
vector<vector<int>> getCustomPuzzle();

int main() {
  cout << "Muntashir's 8-Puzzle Solver." << endl;

  int choice;

  vector<vector<int>> puzzle;
  do {
    // Ask which puzzle to use
    cout << "Type '1' to use a default puzzle, or '2' to enter your own."
         << endl;
    cin >> choice;
    if (choice == 1) {
      puzzle = getDefaultPuzzle();
    } else if (choice == 2) {
      puzzle = getCustomPuzzle();
    } else {
      cout << "Invalid choice. Please try again." << endl;
      // Continue asking until the user gets it right
    }
  } while (choice < 0 || choice > 2);

  // Print the puzzle we got from the user
  printPuzzle(puzzle);

  // Ask which algorithm to use
  cout << "Select algorithm." << endl;
  cout << "1. Uniform Cost Search" << endl;
  cout << "2. A* with Misplaced Tile Heuristic" << endl;
  cout << "3. A* with Manhattan Distance Heuristic." << endl;

  int algoChoice;
  cin >> algoChoice;

  cout << "\nYou chose " << algoChoice << endl;
  // TODO: Choose the actual algorithm

  return 0;
}

void printPuzzle(const vector<vector<int>> &puzzle) {
  cout << "\nCurrent Puzzle State:" << endl;
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      cout << puzzle[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

vector<vector<int>> getDefaultPuzzle() {
  cout << "Using default trivial puzzle..." << endl;
  // Generated from here: https://deniz.co/8-puzzle-solver/
  return {{0, 1, 5}, {3, 6, 2}, {4, 7, 8}};
}

vector<vector<int>> getCustomPuzzle() {
  cout << "Enter your puzzle." << endl;
  cout << "Use 0 to denote the blank. Use space to separate items in each row. "
          "Press enter when done with the row."
       << endl;

  vector<vector<int>> customPuzzle(3, vector<int>(3));

  cout << "First row: ";
  cin >> customPuzzle[0][0] >> customPuzzle[0][1] >> customPuzzle[0][2];

  cout << "Second row: ";
  cin >> customPuzzle[1][0] >> customPuzzle[1][1] >> customPuzzle[1][2];

  cout << "Third row: ";
  cin >> customPuzzle[2][0] >> customPuzzle[2][1] >> customPuzzle[2][2];

  return customPuzzle;
}
