/**
 * CodeObsess (SpawnTree)
 * Copyright © 2018 CodeObsess All rights reserved
 * Complicated Setup : Fix/Refine Setup.
 */

#ifdef __clang__
#pragma clang system_header
#elif defined __GNUC__
#pragma GCC system_header
#endif

#ifndef MIN_RANGE
#define MIN_RANGE 0
#endif

#ifndef MAX_RANGE
#define MAX_RANGE 655369636457
#endif

#include <algorithm>
#include <array>
#include <assert.h>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <list>
#include <map>
#include <math.h>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <time.h>
#include <tuple>
#include <typeinfo>
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using namespace __gnu_pbds;

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
  std::cerr.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
#else
#define trace(...)
#endif

/* #define */
#define abs(x)                                                                 \
  (x < 0 ? (-x) : x) // big bug here if "-x" is not surrounded by "()"
#define LL long long int

#define bit(x, i) (x & (1 << i))          // select the bit of position i of x
#define lowbit(x) ((x) & ((x) ^ ((x)-1))) // get the lowest bit of x
#define hBit(msb, n)                                                           \
  asm("bsrl %1,%0"                                                             \
      : "=r"(msb)                                                              \
      : "r"(n)) // get the highest bit of x, maybe the fastest
#define MOD 10000000007
#define print(vec)                                                             \
  for (const auto &i : vec)                                                    \
    cout << i << endl;
#define fori(vec) for (const auto &i : vec)
#define fill(vec, size)                                                        \
  for (auto i = 0; i < size; i++) {                                            \
    vec.pb(i);                                                                 \
  }
#define input(ss, inputbuffer)                                                 \
  while (cin.good()) {                                                         \
    getline(cin, inputbuffer);                                                 \
    ss << inputbuffer << endl;                                                 \
  }
#define inputLL(j, vec)                                                        \
  while (cin.good()) {                                                         \
    cin >> j;                                                                  \
    vec.pb(j);                                                                 \
  }
#define sz(a) int((a).size())
#define vect(T) std::vector<T>
#define stck(T) std::stack<T>
#define dq(T) std::deque<T>
#define q(T) std::queue<T>
#define arr(T) std::array<T>
#define bits(T) std::bitset<T>
#define SIZE 65536
#define itn int
#define mp make_pair
#define mt make_tuple
#define pb push_back
#define pf push_front
#define popf pop_front
#define popb pop_back
#define max(a, b) (a < b ? b : a)
#define full_all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rev(A) std::reverse(A.begin(), A.end())
#define container_sort(A) std::sort(A.begin(), A.end())
#define present(c, x) ((c).find(x) != (c).end())
#define cpresent(c, x) (find(all(c), x) != (c).end())
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define forvec(container, it)                                                  \
  for (decltype(container.begin()) it = container.begin();                     \
       it != container.end(); it++)
#define Assert(x)                                                              \
  {                                                                            \
    if (!(x)) {                                                                \
      cerr << "Assertion failed at line " << __LINE__ << ": " << #x << " = "   \
           << (x) << "\n";                                                     \
      exit(1);                                                                 \
    }                                                                          \
  }

/* Templates */
template <typename T> T min(T &a, T &b) { return (a < b ? a : b); }
template <typename T> T mod(T &a, T &b) { return (a < b ? a : a % b); }
LL mulmod(LL a, LL b, LL m) {
  LL q = (LL)(((long double)a * (long double)b) / (long double)m);
  LL r = a * b - q * m;
  if (r > m)
    r %= m;
  if (r < 0)
    r += m;
  return r;
}
template <typename T> T expo(T e, T n) {
  T x = 1, p = e;
  while (n) {
    if (n & 1)
      x = x * p;
    p = p * p;
    n >>= 1;
  }
  return x;
}
template <typename T> T power(T e, T n, T m) {
  T x = 1 % m, p = e;
  while (n) {
    if (n & 1)
      x = mod(x * p, m);
    p = mod(p * p, m);
    n >>= 1;
  }
  return x;
}
template <typename T> T extended_euclid(T a, T b, T &x, T &y) {
  T xx = 0, yy = 1;
  y = 0;
  x = 1;
  while (b) {
    T q = a / b, t = b;
    b = a % b;
    a = t;
    t = xx;
    xx = x - q * xx;
    x = t;
    t = yy;
    yy = y - q * yy;
    y = t;
  }
  return a;
}
template <typename T> T mod_inverse(T a, T n) {
  T x, y;
  T d = extended_euclid(a, n, x, y);
  return (d > 1 ? -1 : mod_neg(x, n));
}
template <typename T> T InverseEuler(T a, T m) {
  return (a == 1 ? 1 : power(a, m - 2, m));
}
template <typename T> T gcd(T a, T b) { return (!b) ? a : gcd(b, a % b); }
template <typename T> T lcm(T a, T b) { return (a * (b / gcd(a, b))); }
