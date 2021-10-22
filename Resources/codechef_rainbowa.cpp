/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/RAINBOWA

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

template <class T> struct Compare {
  bool operator()(const T &_lhs, const T &_rhs) { return true; }
};

void solve_problems();

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

void solve_problems() {
  long long int T = 0, N = 0;
  std::cin >> T;
  while (T--) {
    int inp = 0;
    std::cin >> N;
    bool flag = true; /* For exception cases */
    std::vector<int> __input(N, 0);

    for (auto i = 0; i < N; i++) {
      std::cin >> __input[i];
    }

    auto limit = (N / 2) - 1;
    auto j = N - 1;

    for (auto i = 0; i <= limit; i++) {
      if ((__input[i] != __input[j]) ||
          ((__input[i + 1] != __input[i] + 1) &&
           (__input[i + 1] != __input[i])) ||
          (__input[0] != 1) || (__input[limit + 1] != 7)) {
        flag = false;
        std::cout << "no" << std::endl;
        break;
      }
      j--;
    }
    if (flag)
      std::cout << "yes" << std::endl;
  }
}
