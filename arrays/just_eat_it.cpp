// https://omegaup.com/arena/problem/Just-Eat-It/

#include <iostream>
#include <vector>

#define ll long long

void solve(const std::vector<ll int> &);

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  ll int subcases;
  std::cin >> subcases;

  while (subcases--) {
    ll int n;
    std::cin >> n;
    std::vector<ll int> cupcakes(n);
    for (unsigned int i = 0; i < n; i++) {
      std::cin >> cupcakes[i];
    }
    solve(cupcakes);
  }
  return 0;
}

void solve(const std::vector<ll int> &vec) {
  ll int preffix = 0, suffix = 0;

  for (unsigned int i = 1; i <= vec.size(); i++) {
    preffix += vec[i - 1];
    suffix += vec[vec.size() - i];

    if ((suffix <= 0 || preffix <= 0) && i != vec.size()) {
      std::cout << "NO" << std::endl;
      return;
    }
  }

  std::cout << "YES" << std::endl;
}