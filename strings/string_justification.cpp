// https://leetcode.com/problems/text-justification/

#include <iostream>
#include <vector>

std::string process_line(const std::vector<std::string>&, int, int, bool);
std::vector<std::string> solve(const std::vector<std::string>&, int);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::vector<std::string> words;
  int max_width;
  std::cin >> max_width;

  std::string input;
  while(std::getline(std::cin, input)) {
    std::cin >> input;
    words.push_back(input);
  }

  std::vector<std::string> justified_text = solve(words, max_width);
  for (int i = 0; i < justified_text.size(); i++) {
    std::cout << justified_text[i] << std::endl;
  }
  return 0;
}

std::vector<std::string> solve(const std::vector<std::string> &words, int max_width) {
  int index = 0;
  std::vector<std::string> lines;
  while (index < words.size()) {
    int current_width = 0;
    std::vector<std::string> current_line;
    while (current_width + current_line.size() + words[index].length() <= max_width) {
      current_width += words[index].length();
      current_line.push_back(words[index]);
      index++;
      if (index == words.size()) break;
    }

    bool is_last_line = index == words.size();
    lines.push_back(process_line(current_line, current_width, max_width, is_last_line));
  }
  return lines;
}

std::string process_line(const std::vector<std::string> &line, int width, int max_width, bool is_last_line) {
  std::string processed_line;

  if (line.size() == 1) {
    return processed_line = line.front() + std::string(max_width - width, ' ');
  }

  if (is_last_line) {
    for (int i = 0; i < line.size(); i++) {
      processed_line += line[i];
      if (i != line.size() - 1) processed_line += ' ';
    }
    
    return processed_line + std::string(max_width - (width + line.size() - 1), ' ');
  }

  int spaces_between = (max_width - width) / (line.size() - 1);
  int remaining_spaces = max_width - width - spaces_between * (line.size() - 1);
  for (int i = 0; i < line.size(); i++) {
    processed_line += line[i];
    if (i != line.size() - 1) {
      int spaces = spaces_between;
      if (remaining_spaces > 0) {
        spaces++;
        remaining_spaces--;
      }
      
      processed_line += std::string(spaces, ' ');
    }
  }
  return processed_line;
}
