/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/CUTBOARD

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

/* defs */
#define LL unsigned long long
#define Li long long int

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
  /* How many cells to cut in order to not disconnect the complete graph on NxM
   * cells ?? */
  LL T = 0, N = 0, M = 0;
  std::cin >> T;
  while (T--) {
    std::cin >> N >> M;
    std::cout << (N - 1) * (M - 1) << std::endl; // How many cells to cut??
  }
}
