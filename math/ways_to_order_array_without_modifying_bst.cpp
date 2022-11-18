// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/

#include <iostream>
#include <vector>

#define lli long long int
const lli MOD = 1e9 + 7;

struct node {
  int val;
  int size;
  node *left_child;
  node *right_child;
  node(int val) : val(val), size(1), left_child(nullptr), right_child(nullptr) {}
};

void add(int value, node *curr_node) {
  if (value < curr_node->val) {
    if (curr_node->left_child != nullptr) {
      add(value, curr_node->left_child);
    } else {
      curr_node->left_child = new node(value);
    }
  } else {
    if (curr_node->right_child != nullptr) {
      add(value, curr_node->right_child);
    } else {
      curr_node->right_child = new node(value);
    }
  }
  curr_node->size++;
}

class Solution {
public:
  lli numOfWays(std::vector<int> &nums) {
    std::vector<std::vector<lli>> binomial_coeff(nums.size(), std::vector<lli> ());
    for (int i = 0; i < nums.size(); i++) {
      binomial_coeff[i].resize(i + 1);
      for (int j = 0; j <= i; j++) {
        if (j == 0 || j == i) {
          binomial_coeff[i][j] = 1;
        } else {
          lli next_binomial_coeff = (binomial_coeff[i - 1][j - 1] + binomial_coeff[i - 1][j]);
          if (next_binomial_coeff >= MOD) next_binomial_coeff -= MOD;
          binomial_coeff[i][j] = next_binomial_coeff;
        }
      }
    }

    node *root = new node(nums[0]);
    for (int i = 1; i < nums.size(); i++) {
      add(nums[i], root);
    }

    return traverse_tree(root, binomial_coeff) - 1;
  }

  lli traverse_tree(node *curr_node, const std::vector<std::vector<lli>> &binomial_coeff) {
    if (curr_node->size == 1) return 1; // A childless node

    lli num_of_ways_left = 1, num_of_ways_right = 1;
    int min_size = curr_node->size - 1;
    if (curr_node->left_child != nullptr) {
      num_of_ways_left = traverse_tree(curr_node->left_child, binomial_coeff);
      min_size = std::min(min_size, curr_node->left_child->size);
    }
    if (curr_node->right_child != nullptr) {
      num_of_ways_right = traverse_tree(curr_node->right_child, binomial_coeff);
      min_size = std::min(min_size, curr_node->right_child->size);
    }

    lli answer = num_of_ways_left * num_of_ways_right;
    if (answer >= MOD) answer %= MOD;
    answer *= binomial_coeff[curr_node->size - 1][min_size];
    if (answer >= MOD) answer %= MOD;
    return answer;
  }
};