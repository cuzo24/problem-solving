// https://leetcode.com/problems/binary-tree-maximum-path-sum/

#include <iostream>

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
  int maxPathSum(TreeNode* root) {
    auto max_sums = get_max_sums(root);
    return max_sums.first;
  }

  std::pair<int, std::pair<int, int>> get_max_sums(TreeNode *node) {
    // First number of the pair represents the max sum in the subtree and
    // the second pair's first number is the max sum that includes the subtree's root with at most one subtree path
    // the second pair's second value is the max sum that includes the subtree's root
    if (node == nullptr) {
      return std::make_pair(0, std::make_pair(0, 0));
    }
    if (node->left == nullptr && node->right == nullptr) {
      return std::make_pair(node->val, std::make_pair(node->val, node->val));
    }

    std::pair<int, std::pair<int, int>> max_sums_left, max_sums_right;
    max_sums_left = get_max_sums(node->left);
    max_sums_right = get_max_sums(node->right);

    int max_including_node = (
        node->val +
        (max_sums_left.second.first > 0 ? max_sums_left.second.first : 0) +
        (max_sums_right.second.first > 0 ? max_sums_right.second.first : 0)
    );

    int partial_max_including_node = (
        node->val + std::max(std::max(max_sums_left.second.first, max_sums_right.second.first), 0)
    );

    int curr_max = max_including_node;
    if (node->left != nullptr) curr_max = std::max(max_sums_left.first, curr_max);
    if (node->right != nullptr) curr_max = std::max(max_sums_right.first, curr_max);

    return std::make_pair(curr_max, std::make_pair(partial_max_including_node, max_including_node));
  }
};