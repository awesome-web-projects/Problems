/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/CNOTE

#include <bits/stdc++.h>
using namespace std;

/* defs */
#define LL unsigned long long
#define Li unsigned long long int

void solve_problems_for_life();

template <class T> void print(T &cont) {
  for (typename T::iterator itr = cont.begin(); itr != cont.end(); itr++) {
    std::cout << (*(itr)).first << "," << (*(itr)).second << " ";
  }
  std::cout << std::endl;
}

/* Main */
int main(int argc, char *argv[], char *envp[]) {
  auto start = std::chrono::system_clock::now();
  // freopen("input.in", "r+", stdin);
  // freopen("output.txt", "w+", stdout);
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  std::stringstream buffer;
  std::string input = "";
  solve_problems_for_life();

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cerr << std::fixed << "Elapsed time : " << elapsed_seconds.count()
            << "s\n";

  return 0;
}

/* Beta Output Tested */

void solve_problems_for_life() {
  LL T = 0, X = 0, Y = 0, K = 0, N = 0;
  std::cin >> T;
  // assert(1 <= T && T <= 100000);
  while (T--) {
    bool satisfy = false;
    std::cin >> X >> Y >> K >> N;
    LL need = (unsigned long long)(X - Y);
    // assert(1 <= N && N <= 100000);
    while (N--) {
      LL P = 0, C = 0;
      std::cin >> P >> C;
      if ((C <= K) && P >= need) {
        satisfy = true;
      }
    }
    std::cout << ((satisfy == true) ? "LuckyChef" : "UnluckyChef") << "\n";
  }
}
