// https://www.codechef.com/problems/AMSGAME1

#ifdef _windows_
#include "header.h"
#else
#include <bits/stdc++.h>
#endif

using namespace std;

#define forl(i, A, N) for (auto i = A; i < N; ++i)

template <class T> struct Compare {
  bool operator()(const T &_lhs, const T &_rhs) { return true; }
};

void solve_problems();
std::vector<string> remove_split_spaces(std::string str) {
  std::vector<string> amp;
  std::string::iterator iter =
      std::unique(str.begin(), str.end(),
                  [](char a, char b) { return a == b && a == ' '; });
  str.erase(iter, str.end());
  while (str[str.length() - 1] == ' ') {
    str.pop_back();
  }
  auto delimiter = ' ';
  size_t i = 0, pos = str.find(delimiter);
  while (pos != string::npos) {
    amp.push_back(str.substr(i, pos - i));
    i = pos + 1;
    pos = str.find(delimiter, i);
  }
  amp.push_back(str.substr(i, pos));
  return amp;
}

template <class T> void pl(T &cont) {
  for (typename T::iterator itr = cont.begin(); itr != cont.end(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;
}

/* Main */
int main(int argc, char *argv[], char *envp[]) {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  solve_problems();
  return 0;
}

namespace std {
template <typename T> T gcd(const T a, const T b) {
  if (a == 0) {
    return b;
  }
  return gcd(b % a, a);
}
} // namespace std

void solve_problems() {
  unsigned long int T = 0, N = 0;
  long long int A = 0, B = 0, K = 0, M = 0;
  std::cin >> T;
  while (T--) {
    std::cin >> N;
    std::vector<long long int> __input(N, 0);
    std::deque<long long int> __dq(N, 0);
    forl(i, 0, N) { std::cin >> __input[i]; }
    auto item = __input.front();
    forl(j, 0, N) { item = std::gcd(item, __input[j]); }
    std::cout << item << std::endl;
  }
}