// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* remove_nth_from_end(ListNode *&head, int n) {
    int from_end;
    // Since my function for deleting a node needs the node previous to the target to be passed as an
    // argument, I have to create a helper node in case the head is the nth node from end
    aux_function(head, new ListNode(0, head), n, from_end);
    return head;
  }

  void aux_function(ListNode *&head, ListNode *curr_node, int n, int &from_end) {
    if (curr_node == nullptr) {
      from_end = 0;
      return;
    }
    
    aux_function(head, curr_node->next, n, from_end);

    if (from_end == n) {
      remove_next_node(head, curr_node);
    }
    from_end++;
  }

  void remove_next_node(ListNode *&head, ListNode *node) {
    if (node == nullptr || node->next == nullptr) return;
    if (head == node->next) head = head->next;
    node->next = node->next->next;
  }
};

int main() {
  return 0;
}