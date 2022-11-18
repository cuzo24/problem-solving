// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/

#include <iostream>
#include <map>
#include <set>
#include <cstdlib>
#include <time.h>

class RandomizedCollection {
public:
  // maps numbers in our collection to a set which has all the indices that map to the number itself
  std::map<int, std::set<int>> collection;
  // maps indices [0, size-1] to a number in our collection
  std::map<int, int> indices;
  int size;

  RandomizedCollection() {
    srand(time(0));
    size = 0;
  }

  void add_index(int val) {
    std::map<int, int>::iterator it = indices.find(size);
    if (it != indices.end()) it->second = val;
    else indices.insert(std::make_pair(size, val));
  }

  bool insert(int val) {
    add_index(val);

    std::map<int, std::set<int>>::iterator it = collection.find(val);
    if (it == collection.end()) {
      collection.insert(std::make_pair(val, std::set<int> {size++}));
      return true;
    }

    it->second.insert(size++);
    return false;
  }

  bool remove(int val) {
    std::map<int, std::set<int>>::iterator it = collection.find(val);
    if (it == collection.end()) return false;

    // We remove one occurrence of val in our collection
    size--;
    int removed_index = *(it->second.begin());
    if (it->second.size() == 1) {
      collection.erase(val);
    } else {
      it->second.erase(removed_index);
    }
    // Now we have to swap indices with the number in the last position otherwise we would end up
    // with gaps in [0, size - 1]
    std::map<int, std::set<int>>::iterator last_element = collection.find(indices[size]);
    last_element->second.erase(size);
    if (indices[size] != val) {
      indices[removed_index] = indices[size];
    }
    last_element->second.insert(removed_index);

    return true;
  }

  int getRandom() {
    int number = rand() % size;
    return indices[number];
  }
};