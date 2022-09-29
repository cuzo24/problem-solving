// https://leetcode.com/problems/simplify-path/

#include <iostream>
#include <vector>

std::string construct_path(const std::vector<std::string>&);
std::vector<std::string> parse_segments(const std::vector<std::string>&);
std::string solve(const std::string&);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string path;
  std::cin >> path;
  std::cout << solve(path) << std::endl;
  return 0;
}

std::string solve(const std::string &path) {
  std::vector<std::string> path_segments;
  bool new_segment;

  for (int i = 0; i < path.length(); i++) {
    if (path[i] == '/') {
      new_segment = true;
      continue;
    }

    if (new_segment) {
      new_segment = false;
      path_segments.push_back(std::string(1, path[i]));
    } else {
      path_segments.back().push_back(path[i]);
    }
  }

  return construct_path(parse_segments(path_segments));
}

std::vector<std::string> parse_segments(const std::vector<std::string> &segments) {
  std::vector<std::string> canonical_path_segments;
  for (int i = 0; i < segments.size(); i++) {
    if (segments[i] == ".") continue;
    if (segments[i] == "..") {
      if (canonical_path_segments.size() > 0) canonical_path_segments.pop_back();
    } else {
      canonical_path_segments.push_back(segments[i]);
    }
  }
  return canonical_path_segments;
}

std::string construct_path(const std::vector<std::string> &segments) {
  std::string path = "/";
  for (int i = 0; i < segments.size(); i++) {
    path += segments[i];
    if (i != segments.size() - 1) path += "/";
  }
  return path;
}