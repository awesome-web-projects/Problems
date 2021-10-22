/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/FRGTNLNG

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

/* defs */
#define LL unsigned long long
#define Li long long int

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
  int T = 0, N = 0, K = 0, L = 0;
  std::string str;
  std::stringstream buffer;
  std::vector<std::string> old_lang;
  std::unordered_set<std::string> modern;
  std::cin >> T;
  while (T--) {
    old_lang.clear();
    modern.clear();
    std::cin >> N >> K;
    std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
    while (N--) {
      str.clear();
      std::cin >> str;
      old_lang.emplace_back(str);
    }
    while (K--) {
      std::cin >> L;
      while (L--) {
        str.clear();
        std::cin >> str;
        modern.insert(str);
      }
    }
    for (const auto &found : old_lang) {
      if (modern.find(found) != modern.end()) {
        std::cout << "YES ";
      } else {
        std::cout << "NO ";
      }
    }
    std::cout << std::endl;
  }
}
