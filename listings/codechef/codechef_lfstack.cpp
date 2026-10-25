// https://www.codechef.com/problems/LFSTACK

#ifdef _windows_
#include "header.h"
#else
#include <bits/stdc++.h>
#endif

namespace std {
template <typename T> T gcd(const T a, const T b) {
  if (a == 0) {
    return b;
  }
  return gcd(b % a, a);
}
} // namespace std

using namespace std;

#define forl(i, A, N) for (long long int i = A; i < N; i++)

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

template <class T> void p(T &cont) {
  for (typename T::iterator itr = cont.begin(); itr != cont.end(); itr++) {
    std::cout << *itr << ", ";
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

int sum = 0LL;
std::vector<long long int> sequence;
std::map<std::vector<long long int>, bool> map_stack_push_pop;
std::vector<std::vector<long long int>> stacks;

bool map_record_state_moves(long long int now,
                            std::vector<long long int> &state) {
  if (map_stack_push_pop.find(state) != map_stack_push_pop.end()) {
    // memoized return from mapping we are storing.
    return map_stack_push_pop[state];
  }
  if (now == sum) {
    // check if all stacks are empty, it should have been empty by now, since we
    // are poping elements on a match.
    forl(j, 0, state.size()) {
      if (state[j] != 0)
        return false;
    }
    return true;
  }
  /** Long story mode now (:->)
          What we actaully want to see is that given a number from the seqeunce,
     do we get a way to produce that number at that given position by poping
     elements from the stacks as done by the threads. Now, we may be able to
     produce the number by the current no of elements that have been poped till
     now or by poping a new element and seeing if that helps in making the
     sequence till the number we consider in at the given state. We intially
     consider that it is not possible. When there are more than one ways of
     making a sequence by poping from one or more stacks, there is no method to
     tell as to which stack to always choose greedily. We thus have to go for a
     dynamic programming approach.
  */
  bool current = false;
  // For all the stacks available, we consider the top element of each stack
  // right now and process as explained above.
  forl(i, 0, state.size()) {
    if (stacks[i][state[i]] == sequence[now]) {
      // Pop element.
      state[i]--;
      current = map_record_state_moves(now + 1, state);
      // Consider by not poping it. Similar to what we did in Subset Sums
      // dynamic programming.
      state[i]++;
      if (current)
        break;
    }
  }
  map_stack_push_pop[state] = current;
  return current;
}

void solve_problems() {
  unsigned long int T = 0, N = 0;
  long long int A = 0, B = 0, K = 0, M = 0;
  std::cin >> T;
  while (T--) {
    sum = 0LL;
    std::cin >> N;
    // states[i] records the number of intergers left to be considered in a
    // given stack i.
    std::vector<long long int> states;
    stacks.clear();
    sequence.clear();
    map_stack_push_pop.clear();
    stacks.resize(N);
    forl(i, 0, N) {
      std::cin >> K;
      sum += K;
      stacks[i].resize(K + 1);
      forl(j, 0, K) { std::cin >> stacks[i][j + 1]; }
      // End of the stack identifer. Push it in the sequence also.
      stacks[i][0] = std::numeric_limits<long long int>::min();
      states.push_back(K);
    }
    // Store the sequence.
    sequence.resize(sum);
    forl(j, 0, sum) { std::cin >> sequence[j]; }
    // Actual processing now.
    if ((N != 1) && map_record_state_moves(0, states)) {
      std::cout << "Yes" << std::endl;
    } else if (N == 1) {
      // Only one thread, just reverse the given sequence and check if it
      // matches the stack push order.
      sequence.push_back(stacks[0][0]);
      std::reverse(sequence.begin(), sequence.end());
      if (sequence == stacks[0]) {
        std::cout << "Yes" << std::endl;
      } else {
        // Nope there is a mismatch.
        std::cout << "No" << std::endl;
      }
    } else {
      // Sequence can't be formed by successive pop operations by threads.
      std::cout << "No" << std::endl;
    }
  }
}
