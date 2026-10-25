// https://www.codechef.com/problems/VALIDSTK
/* SpawnTree (CodeObsess Sumit Lahiri) */

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
  unsigned int T = 0, N = 0;
  std::cin >> T;
  while (T--) {
    unsigned int push = 0, pop = 0, inp = 0;
    bool flag = false;
    std::cin >> N;
    while (N--) {
      std::cin >> inp;
      (inp) ? (++push) : (++pop);
      if (pop > push) {
        flag = true;
      }
    }
    std::cout << ((flag) ? "Invalid" : "Valid") << "\n";
  }
}
