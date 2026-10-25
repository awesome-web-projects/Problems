**A. Subset Selecting — Complete C++20 Solution**

[Original problem](https://codeforces.com/contest/2277/problem/A) · [C++ source](A.cpp)

**Problem in brief**

Given an array and a minimum group size `k`, select disjoint groups of at least `k` elements. Some elements may remain unused. Each group contributes its maximum; maximize the MEX of those maxima. MEX means the smallest missing nonnegative integer.

Each test case supplies `n k`, then `n` integers. Print one maximum MEX. Here `1 <= k <= n <= 100` and `0 <= a[i] <= n`.

**Algorithm and correctness**

To obtain a MEX of at least `q`, we need groups whose maxima are `0,1,...,q-1`. Extra groups do not help. We can also restrict every useful group to exactly `k` elements: keep one occurrence of its maximum and any `k-1` other elements.

This suggests processing the required maxima in increasing order. Let `available` count unused elements whose values are at most the current maximum `v`.

Add `frequency[v]` to `available`. A group with maximum `v` exists precisely when both conditions hold:

- `frequency[v] > 0`, so the maximum itself is present;
- `available >= k`, so there are enough elements for the group.

On success, consume `k` elements. Otherwise, stop and return `v`.

Why can we ignore which particular elements were consumed? Every earlier group has maximum smaller than `v`, so no occurrence of `v` has been consumed. All other available elements are interchangeable as fillers: every later maximum permits all of them. Using exactly `k` elements also leaves as many fillers as possible for later groups. Thus a failure cannot be repaired by changing earlier choices, and every successful step is safe.

For example, with `k=2` and `[0,0,0,1,1,2]`, choose `{0,0}`, `{0,1}`, and `{1,2}`. Their maxima are `0,1,2`, giving MEX `3`.

Time: **O(n)**. Extra space: **O(n)**.

**Example input**

```text
4
6 2
0 0 0 1 1 2
3 2
0 1 2
4 1
0 1 1 2
4 2
0 0 2 2
```

**Example output**

```text
3
0
3
1
```

**Worked examples**

These are custom examples.

1. With `k=2`, form `{0,0}`, `{0,1}`, and `{1,2}`. Their maxima are `0,1,2`, so the MEX is `3`. Six elements cannot support four groups of size two, so no larger result is possible.
2. A maximum-zero group needs two zeros, but only one exists. The MEX stays `0`.
3. With `k=1`, singleton groups containing `0`, `1`, and `2` give MEX `3`.
4. The two zeros form a maximum-zero group. There is no `1`, so no maximum-one group can exist; the answer is `1`.

The first example's count trace is:

| Required maximum | New elements | Available before grouping | Used | Left |
|---|---:|---:|---:|---:|
| 0 | 3 | 3 | 2 | 1 |
| 1 | 2 | 3 | 2 | 1 |
| 2 | 1 | 2 | 2 | 0 |
| 3 | 0 | 0 | Cannot create maximum 3 | 0 |

The output counts successful groups: `3`.

**Implementation notes**

The program stores `frequency[0..n]`. Before each attempt, `available` contains every unused element that can belong to a group with this maximum. It checks for an actual occurrence of the maximum as well as enough fillers. This distinction matters: a large pool of zeros cannot produce maximum one if no one occurs.

**Complete C++20 code**

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> frequency(n + 1);
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            ++frequency[x];
        }
        int answer = 0, available = 0;
        for (int value = 0; value <= n; ++value) {
            available += frequency[value];
            if (frequency[value] == 0 || available < k) break;
            available -= k;
            ++answer;
        }
        cout << answer << '\n';
    }
}
```

**Build and run**

```sh
g++ -std=c++20 -O2 -Wall -Wextra A.cpp -o A
./A < input.txt
```

Save the example input as `input.txt`. The first number is the number of test cases. On Windows, run the corresponding `.exe`.

**Validation**

The C++ source was compiled and checked locally. See [validation details](VALIDATION.md) and the [test script](test_solutions.py). The code block above matches `A.cpp` exactly.
