#include <headers.h>
extern void solution(void);

int main(int argc, char **argv, char **envp) {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(NULL);

  freopen("../inputs/inputs.txt", "r", stdin);
  /**
   * Take input from the stdin, Eg.
   * std::cin >> a;
   * std::cin.getline(std::cin, str);
   *
   * Print output to stdout
   * use std::endl for "\n", endline Eg.
   * std::cout << a << std::endl;*
   */

  // Don't change return code to -1.
  solution();

  return 0;
}
