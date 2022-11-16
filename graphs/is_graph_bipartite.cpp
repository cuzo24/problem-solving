// https://leetcode.com/problems/is-graph-bipartite/

#include <vector>

class Solution {
public:
  bool is_bipartite(const std::vector<std::vector<int>> &graph) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<int> colors(graph.size());
    int total_visited = 0;

    for (int i = 0; i < graph.size(); i++) {
      if (!visited[i]) {
        total_visited++;
        visited[i] = true;
        colors[i] = 0;
        if(!traverse(graph, visited, colors, i, 0, total_visited)) {
          return false;
        };
      }
    }

    return true;
  }

  bool traverse(
    const std::vector<std::vector<int>> &graph,
    std::vector<bool> &visited, std::vector<int> &colors,
    int current_node, int prev_color, int &count
  ) {
    for (int v : graph[current_node]) {
      if (!visited[v]) {
        count++;
        visited[v] = true;
        colors[v] = prev_color ^ 1;
        if (!traverse(graph, visited, colors, v, prev_color ^ 1, count)) {
          return false;
        };
      } else if (colors[v] == prev_color) return false;
    }

    return true;
  }
};