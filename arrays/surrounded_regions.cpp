// https://leetcode.com/problems/surrounded-regions/

#include <iostream>
#include <vector>
#include <map>  

struct dsu {
  std::vector<int> parent;
  std::vector<int> size;
  std::vector<bool> touches_border;

  dsu(int n, const std::vector<bool> &is_border) {
    parent.resize(n);
    size.resize(n);
    touches_border.resize(n);

    for (int i = 0; i < n; i++) {
      parent[i] = i;
      size[i] = 1;
      touches_border[i] = is_border[i];
    }
  }

  int get_representative(int u) {
    if (parent[u] == u) return u;
    else return parent[u] = parent[parent[u]];
  }

  void merge(int u, int v) {
    u = get_representative(u);
    v = get_representative(v);
    if (u == v) return;
    if (size[u] > size[v]) {
      std::swap(u, v);
    }  
    parent[u] = v;
    parent[v] = v;
    size[v] += size[u];
    size[u] = size[v];
    touches_border[u] = touches_border[v] || touches_border[u];
    touches_border[v] = touches_border[u];
  }
};

class Solution {
public:
  void solve(std::vector<std::vector<char>> &board) {
    std::map<std::pair<int, int>, int> mp;
    std::vector<bool> is_border;
    int o_cells = 0, n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 'O') {
          is_border.push_back(i == 0 || i + 1 == n || j == 0 || j + 1 == m);
          mp.insert({std::make_pair(i, j), o_cells});
          o_cells++;
        }
      }
    }
    dsu my_dsu = handle_dsu(mp, o_cells, n, m, is_border);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 'O') {
          std::pair<int, int> current_cell = std::make_pair(i, j);
          std::map<std::pair<int, int>, int>::iterator it = mp.find(current_cell);
          int representative_index = my_dsu.get_representative(it->second);
          if (!my_dsu.touches_border[representative_index]) {
            board[i][j] = 'X';
          }
        }
      }
    }

    return;
  }

  dsu handle_dsu(std::map<std::pair<int, int>, int> &mp, int size, int n, int m, const std::vector<bool> &is_border) {
    dsu my_dsu(size, is_border);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        std::pair<int, int> current_cell = std::make_pair(i, j);
        std::map<std::pair<int, int>, int>::iterator it = mp.find(current_cell);
        if (it != mp.end()) {
          if (i > 0) check(it->second, std::make_pair(i - 1, j), mp, my_dsu);
          if (i + 1 < n) check(it->second, std::make_pair(i + 1, j), mp, my_dsu);
          if (j > 0) check(it->second, std::make_pair(i, j - 1), mp, my_dsu);
          if (j + 1 < m) check(it->second, std::make_pair(i, j + 1), mp, my_dsu);
        }
      }
    }
    return my_dsu;
  }

  void check(int u, std::pair<int, int> v, std::map<std::pair<int, int>, int> &mp, dsu &my_dsu) {
    std::map<std::pair<int, int>, int>::iterator it = mp.find(v);
    if (it != mp.end()) {
      my_dsu.merge(u, it->second);
    }
  }
};

int main() {
  Solution a;
  std::vector<std::vector<char>> board{{'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};
  a.solve(board);
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}