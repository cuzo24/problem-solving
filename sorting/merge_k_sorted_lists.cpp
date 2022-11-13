// https://leetcode.com/problems/merge-k-sorted-lists/

#include <iostream>
#include <vector>

class MinHeap {
public:
  std::vector<std::pair<int, int>> heap;
  int size;
  int maxsize;

  MinHeap(int maxsize) {
    this->maxsize = maxsize;
    this->size = 0;
    heap.resize(maxsize);
  }

  int parent(int pos) { return (pos - 1) / 2; }

  int left_child(int pos) { return (2 * pos) + 1; }

  int right_child(int pos) { return (2 * pos) + 2; }

  bool is_leaf(int pos) {
    return (pos > (size / 2) && pos < size);
  }

  void swap(int fpos, int spos) {
    std::pair<int, int> tmp;
    tmp = heap[fpos];
    heap[fpos] = heap[spos];
    heap[spos] = tmp;
  }

  void heapify(int pos) {
    if (is_leaf(pos)) return;

    int left = left_child(pos);
    int right = right_child(pos);

    if (
      (left < size && heap[pos].first > heap[left].first) ||
      (right < size &&heap[pos].first > heap[right].first)
    ) {
      if (left < size && heap[left].first < heap[right].first) {
        swap(pos, left);
        heapify(left);
      } else {
        swap(pos, right);
        heapify(right);
      }
    }
  }

  void insert(std::pair<int, int> element) {
    heap[size] = element;

    int current = size;
    while (heap[current].first < heap[parent(current)].first) {
      swap(current, parent(current));
      current = parent(current);
    }
    size++;
  }

  std::pair<int, int> extract_min() {
    std::pair<int, int> popped = heap[0];
    heap[0] = heap[--size];
    heapify(0);
    return popped;
  }
};

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* merge_k_lists(std::vector<ListNode*> &lists) {
    ListNode *head = nullptr, *tail = nullptr;
    int k = lists.size();

    MinHeap *heap = new MinHeap(k);
    for (int i = 0; i < k; i++) {
      if (lists[i] == nullptr) continue;
      heap->insert(std::make_pair(lists[i]->val, i));
      lists[i] = lists[i]->next;
    }

    while (heap->size != 0) {
      std::pair<int, int> extracted = heap->extract_min();
      ListNode *next_node = new ListNode(extracted.first);

      if (tail == nullptr) {
        head = next_node;
      } else {
        tail->next = next_node;
      }
      tail = next_node;

      if (lists[extracted.second] != nullptr) {
        heap->insert(std::make_pair(lists[extracted.second]->val, extracted.second));
        lists[extracted.second] = lists[extracted.second]->next;
      }
    }

    return head;
  }
};

int main() {
  return 0;
}