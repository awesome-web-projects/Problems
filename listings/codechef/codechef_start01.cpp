/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/START01

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

/* Trace for recursions. */
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1> void __f(const char *name, Arg1 &&arg1) {
  std::cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args) {
  const char *comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
#else
#define trace(...)
#endif

/* defs */
#define LL unsigned long long
#define Li long long int

void solve_problems();

template <class T> void _PrinT(T &cont) {
  for (typename T::iterator itr = cont.begin(); itr != cont.end(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;
}

/* Main */
int main(int argc, char *argv[], char *envp[]) {
  auto start = std::chrono::system_clock::now();
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  solve_problems();
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cerr << std::fixed << "Elapsed time : " << elapsed_seconds.count()
            << "s, Program Executed Successfully. Press Ctrl + S to "
               "re-compile. (Output Synced). "
            << "Finished computation at : " << std::ctime(&end_time);
  return 0;
}

void solve_problems() {
  long long int T;
  std::cin >> T;
  std::cout << T << std::endl;
}
