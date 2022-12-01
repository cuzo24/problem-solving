// https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/

#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct output {
  bool is_bst;
  int sum;
  int min_value;
  int max_value;

  output(bool is_bst) : is_bst(is_bst), sum(0) {}
  output(
      bool is_bst, int sum, int min, int max
  ) : is_bst(is_bst), sum(sum), min_value(min), max_value(max) {}
};

class Solution {
public:
  int maxSumBST(TreeNode* root) {
    int max = 0;
    dfs(root, max);
    return max;
  }

  output dfs(TreeNode *node, int &max_sum) {
    if (node == nullptr) return output(true);

    auto left = dfs(node->left, max_sum), right = dfs(node->right, max_sum);
    if (
        left.is_bst && right.is_bst &&
        (node->left == nullptr || left.max_value < node->val) &&
        (node->right == nullptr || right.min_value > node->val)
    ) {
      int curr_sum = left.sum + right.sum + node->val;
      int min = (node->left != nullptr ? left.min_value : node->val);
      int max = (node->right != nullptr ? right.max_value : node->val);

      max_sum = std::max(max_sum, curr_sum);
      return output(true, curr_sum, min, max);
    }

    return output(false);
  }
};