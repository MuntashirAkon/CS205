#include "Node.h"
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;

// Prints the given puzzle
void printPuzzle(const vector<vector<int>> &puzzle) {
  for (int i = 0; i < puzzle.size(); i++) {
    for (int j = 0; j < puzzle[i].size(); j++) {
      cout << puzzle[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

// Checks if the current state matches the target goal state
bool isGoal(const vector<vector<int>> &state) {
  vector<vector<int>> goal_state = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
  return state == goal_state;
}

int calculateMisplacedTile(const vector<vector<int>> &state) {
  // TODO:
  return 0;
}

int calculateManhattanDistance(const vector<vector<int>> &state) {
  // TODO:
  return 0;
}

// Utility function to calculate h(n) given algorithm
int calculateHeuristic(const vector<vector<int>> &state, int algorithm_choice) {
  int initial_h = 0;
  if (algorithm_choice == 1) {
    // Uniform Cost Search = A* with h(n) = 0
    return 0;
  } else if (algorithm_choice == 2) {
    // A* with Misplaced Tile Heuristic
    return calculateMisplacedTile(state);
  } else if (algorithm_choice == 3) {
    // A* with Manhattan Distance Heuristic
    return calculateManhattanDistance(state);
  } else {
    cout << "Invalid algorithm. Done." << endl;
    exit(0);
  }
}

// Generates child nodes by moving the blank space up, down, left, and right
vector<Node *> expand(Node *current_node, int algorithm_choice) {
  vector<Node *> children;
  int zero_row = -1;
  int zero_col = -1;

  // Find the coordinates of the blank space
  for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
      if (current_node->state[row][col] == 0) {
        zero_row = row;
        zero_col = col;
        break;
      }
    }
  }

  // Define the 4 possible moves (up, down, left, right)
  // Represented as (row_offset, col_offset)
  vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  // Generate a child state for each valid move
  for (auto move : moves) {
    int new_row = zero_row + move.first;
    int new_col = zero_col + move.second;

    // Check if the move stays within the 3x3 grid boundaries
    if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
      // Copy the current state
      vector<vector<int>> new_state = current_node->state;

      // Slide the tile by swapping the 0 with the target tile
      swap(new_state[zero_row][zero_col], new_state[new_row][new_col]);

      // Calculate costs
      int new_g = current_node->g + 1;
      int new_h = calculateHeuristic(new_state, algorithm_choice);

      // Create the new child node
      Node *child = new Node(new_state, current_node, new_g, new_h);
      children.push_back(child);
    }
  }

  return children;
}

// Peform the actual search given initial state and the algorithm
void generalSearch(const vector<vector<int>> &initial_state,
                   int algorithm_choice) {
  // Store the states that were previously visited
  set<vector<vector<int>>> visited_states;
  // Calculate initial h(n)
  int initial_h = calculateHeuristic(initial_state, algorithm_choice);

  // E.g. nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
  priority_queue<Node *, vector<Node *>, NodeComparator> nodes;
  Node *starting_node = new Node(initial_state, nullptr, 0, initial_h);
  nodes.push(starting_node);

  int max_queue_size = 0;
  int num_nodes_expanded = 0;

  while (true) { // Infinite loop
    // if EMPTY(nodes) then return "failure"
    if (nodes.empty()) {
      cout << "Failure: No solution found. Done." << endl;
      return;
    }

    // Update max queue size
    if (nodes.size() > max_queue_size) {
      max_queue_size = nodes.size();
    }

    // node = REMOVE-FRONT(nodes)
    Node *node = nodes.top();
    nodes.pop();

    cout << "[Depth " << node->g << "] "
         << "The best state to expand with a g(n) = " << node->g
         << " and h(n) = " << node->h << " is:" << endl;
    printPuzzle(node->state);

    // problem.GOAL-TEST(node.STATE)
    if (isGoal(node->state)) {
      cout << "Goal state!" << endl;
      cout << "\nSolution depth: " << node->g << endl;
      cout << "Number of nodes expanded: " << num_nodes_expanded << endl;
      cout << "Max queue size: " << max_queue_size << endl;
      return;
    }

    // Check if we've already seen this state
    if (visited_states.find(node->state) != visited_states.end()) {
      // Skip if we've already evaluated this state
      continue;
    }

    // Add the current board state to our visited set
    visited_states.insert(node->state);

    num_nodes_expanded++;

    // nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
    vector<Node *> children = expand(node, algorithm_choice);
    for (Node *child : children) {
      // Check if the child state is already in visited_states
      if (visited_states.find(child->state) == visited_states.end()) {
        // Haven't visited yet.
        nodes.push(child);
      } else {
        // Already visited this node.
        delete child;
      }
    }
  }
}
