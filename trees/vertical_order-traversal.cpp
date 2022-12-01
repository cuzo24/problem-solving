// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  std::vector<std::vector<int>> verticalTraversal(TreeNode *root) {
    std::map<int, int> column_indices;
    std::vector<std::vector<std::pair<int, int>>> columns;
    dfs(root, column_indices, columns);

    std::vector<std::vector<int>> answer;
    answer.reserve(columns.size());

    for (auto it = column_indices.begin(); it != column_indices.end(); it++) {
      answer.push_back(std::vector<int> ());
      int index = it->second;
      std::sort(
          columns[index].begin(), columns[index].end(),
          [](std::pair<int, int> a, std::pair<int, int> b) {
              return a.first == b.first ? a.second < b.second : a.first < b.first;
          }
      );
      for (int j = 0; j < columns[index].size(); j++) {
        answer.back().push_back(columns[index][j].second);
      }
    }

    return answer;
  }

  void dfs(
      TreeNode *node, std::map<int, int> &column_indices,
      std::vector<std::vector<std::pair<int, int>>> &columns, int row = 0, int col = 0
  ) {
    std::pair<int, int> pair = std::make_pair(row, node->val);

    auto it = column_indices.find(col);
    if (it == column_indices.end()) {
      column_indices.insert(std::make_pair(col, columns.size()));
      columns.push_back(std::vector<std::pair<int, int>> {pair});
    } else {
      columns[it->second].push_back(pair);
    }

    if (node->left != nullptr) dfs(node->left, column_indices, columns, row + 1, col - 1);
    if (node->right != nullptr) dfs(node->right, column_indices, columns, row + 1, col + 1);
  }

};