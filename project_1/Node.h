#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>

using namespace std;

// Denotes a puzzle state
struct Node {
  // The actual puzzle
  vector<vector<int>> state;
  // Cost from start node to current node, g(n)
  int g;
  // Heuristic cost to goal, h(n)
  int h;

  // Constructor
  Node(vector<vector<int>> s, int g_cost, int h_cost)
      : state(s), g(g_cost), h(h_cost) {}

  // We use a priority queue here from STL instead of developing one from
  // scratch. It needs to order by f(n) = g(n) + h(n). We overload the >
  // operator to create a min-heap.
  bool operator>(const Node &other) const {
    int this_f = this->g + this->h;
    int other_f = other.g + other.h;
    return this_f > other_f;
  }
};

#endif