#include "Node.h"
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

// Peform the actual search given initial state and the algorithm
void generalSearch(const vector<vector<int>> &initial_state,
                   int algorithm_choice) {
  // Store the states that were previously visited
  set<vector<vector<int>>> visited_states;

  int initial_h = 0;
  if (algorithm_choice == 1) {
    // Uniform Cost Search = A* with h(n) = 0
    initial_h = 0;
  } else if (algorithm_choice == 2) {
    // A* with Misplaced Tile Heuristic
    initial_h = calculateMisplacedTile(initial_state);
  } else if (algorithm_choice == 3) {
    // A* with Manhattan Distance Heuristic
    initial_h = calculateManhattanDistance(initial_state);
  } else {
    cout << "Invalid algorithm. Done." << endl;
    return;
  }

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
      cout << "\nGoal state!" << endl;
      cout << "\nSolution depth was " << node->g << endl;
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

    // TODO: nodes = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
  }
}
