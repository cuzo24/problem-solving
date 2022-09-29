// https://omegaup.com/arena/problem/Ejercicio-ANIEI/

#include <iostream>
#include <vector>
#include <algorithm>

std::string sort_letters_array(const std::string &letters)
{
  std::string result(letters);
  std::sort(result.begin(), result.end(), [](char e1, char e2)
            { return e1 - 'a' < e2 - 'a'; });
  return result;
}

std::vector<std::string> weird_string_sorter(const std::vector<std::string> &prev_sort, const std::string &last_col)
{
  int n = last_col.length();
  std::vector<std::string> result(n);
  std::vector<int> order(n);
  for (int i = 0; i < last_col.length(); i++)
  {
    order[i] = i;
  }

  std::sort(order.begin(), order.end(), [last_col](int i, int j)
            { return (last_col[i] != last_col[j]) ? (last_col[i] - 'a' < last_col[j] - 'a') : (i < j); });

  for (int i = 0; i < last_col.length(); i++)
  {
    result[i] = last_col[order[i]] + prev_sort[order[i]];
  }

  return result;
}

void solve(const std::string &s)
{
  int n = s.length();
  std::vector<std::string> sorted_rotation(n);

  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      std::string aux = sort_letters_array(s);
      for (int j = 0; j < n; j++)
      {
        sorted_rotation[j] = aux[j];
      }
    }
    else
    {
      sorted_rotation = weird_string_sorter(sorted_rotation, s);
    }
  }

  std::cout << sorted_rotation[0].substr(1) << std::endl;

  return;
}

int main()
{
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string input;
  while (std::getline(std::cin, input))
  {
    solve(input);
  }
  return 0;
}

// Unused code
// std::vector<std::vector<char>> sort_ngrams(const std::vector<char> &first_rot, const std::vector<char> &last_rot) {

// }

// std::vector<char> get_possible_next_letter(char letter, const std::vector<char> &first_rot, const std::vector<char> &last_rot)
// {
//   std::vector<char> possibles;
//   for (int i = 0; i < last_rot.size(); i++)
//   {
//     if (last_rot[i] == letter)
//       possibles.push_back(first_rot[i]);
//   }
//   return possibles;
// }

// std::vector<char> get_next_rotation(const std::vector<char> &prev_rot, const std::vector<char> &first_rot, const std::vector<char> &letters)
// {
//   int length = prev_rot.size();
//   std::vector<char> result;
//   std::vector<bool> done(length, false);
//   for (int i = 0; i < length; i++)
//   {
//     if (done[i])
//       continue;

//     std::vector<char> possibles = get_possible_next_letter(prev_rot[i], first_rot, letters);
//     if (possibles.size() == 1)
//     {
//       result[i] = possibles[0];
//       done[i] = true;
//     }
//     else
//     {
//       // std::vector<char> sorted_possibles =
//     }
//   }
//   // std::vector<char> result(letters);
//   std::sort(result.begin(), result.end(), [](char e1, char e2)
//             { return e1 - 'a' < e2 - 'a'; });
//   return result;
// }

// bool naive_string_comp(const std::string &str1, const std::string &str2)
// {
//   int length1 = str1.length();
//   int length2 = str2.length();
//   for (int i = 0; i < std::min(length1, length2); i++)
//   {
//     if (str1[i] != str2[i])
//       return str1[i] - 'a' < str2[i] - 'a';
//   }

//   return length1 < length2;
// }