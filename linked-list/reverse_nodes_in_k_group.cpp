// https://leetcode.com/problems/reverse-nodes-in-k-group/https://leetcode.com/problems/reverse-nodes-in-k-group/

#include <iostream>

struct List_node {
  int val;
  List_node *next;
  List_node() : val(0), next(nullptr) {}
  List_node(int x) : val(x), next(nullptr) {}
  List_node(int x, List_node *next) : val(x), next(next) {}
};

class Solution {
public:
  List_node* reverse_k_group(List_node* head, int k) {
    List_node *first_ptr = head, *second_ptr = head, *previous = nullptr;
    int count = 0, first = true;
    while (second_ptr != nullptr) {
      count++;
      List_node *next = second_ptr->next;
      if (count == k) {
        List_node *tmp1 = first_ptr;
        List_node *tmp2 = first_ptr->next;
        for (int i = 1; i < k; i++) {
          List_node *aux = tmp2->next;
          tmp2->next = tmp1;
          tmp1 = tmp2;
          tmp2 = aux;
        }
        if (first) {
          head = second_ptr;
          first = false;
        } else {
          previous->next = second_ptr;
        }
        previous = first_ptr;
        second_ptr = first_ptr;
        first_ptr->next = next;
        first_ptr = next;
        count = 0;
      }
      second_ptr = second_ptr->next;
    }
    return head;
  }
};

void print_list(List_node *head) {
  while (head != nullptr) {
    std::cout << head->val;
    if (head->next != nullptr) std::cout << " -> ";
    head = head->next;
  }
  std::cout << std::endl;
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  Solution o;
  List_node last(5);
  List_node fourth(4, &last);
  List_node third(3, &fourth);
  List_node second(2, &third);
  List_node head(1, &second);

  print_list(&head);
  List_node *ans = o.reverse_k_group(&head, 2);
  print_list(ans);
  return 0;
}