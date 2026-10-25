**B. Sequence Decreasing — Complete C++20 Solution**

[Original problem](https://codeforces.com/contest/2277/problem/B) · [C++ source](B.cpp)

**Problem in brief**

An operation selects a nonempty contiguous segment whose elements are all positive, decreases every selected element by one, and deletes one selected element. An array is good if it can become a nonempty all-zero array. Find the longest good subsequence of the given array, or print `0` if none exists.

Each test case supplies `n`, then `n` nonnegative integers. Print the maximum length. The sum of `n` is at most `200000`, and values may be as large as `10^9`.

**Algorithm and correctness**

The answer is always either the entire length `n` or zero:

`answer = n` if `min(a) < n`; otherwise `answer = 0`.

Here is the construction behind that surprisingly short condition. If a zero already exists, keep it and delete every positive element by operating on that element alone. A singleton operation can delete a positive element regardless of its magnitude.

Otherwise let the minimum value be `m`, with `1 <= m < n`, and select an occurrence of it to preserve. Operate on the whole remaining array `m` times, each time deleting a different element from the selected minimum. Before the last operation, all remaining values are positive: each started at least `m`, and fewer than `m` decrements have occurred. After the last operation, the preserved element is zero, and at least one element remains because `m < n`. Delete all remaining positive elements individually. Thus the full array is good.

For impossibility, consider any subsequence of length `L`. Before its first zero appears, the element becoming zero must survive as many operations as its initial value. Every operation removes an element, so a survivor can have experienced at most `L-1` operations. If every original value is at least `n`, it is also at least `L`, making the first zero impossible. No nonempty good subsequence exists.

Time: **O(n)**. Extra space: **O(1)**.

**Example input**

```text
5
1
0
1
1
3
5 3 4
4
2 5 4 7
5
2 1 1 0 3
```

**Example output**

```text
1
0
0
4
5
```

**Worked examples**

These are custom examples.

- `[0]` is already good, so the answer is `1`.
- `[1]` cannot become a nonempty zero array: its only possible operation deletes its only element. The answer is `0`.
- In `[5,3,4]`, every value is at least the array length. No subsequence can create its first surviving zero, so the answer is `0`.
- In `[2,5,4,7]`, the minimum is `2 < 4`. Preserve the first element and perform the following legal steps:

| Current array | Chosen segment | After decrement | Deleted element | Remaining array |
|---|---|---|---|---|
| `[2,5,4,7]` | Whole array | `[1,4,3,6]` | Last, now 6 | `[1,4,3]` |
| `[1,4,3]` | Whole array | `[0,3,2]` | Last, now 2 | `[0,3]` |
| `[0,3]` | Singleton containing 3 | `[0,2]` | The selected 2 | `[0]` |

The full original sequence is good, so its length `4` is the answer.

In the last test, a zero already exists. Delete each positive element using singleton operations and retain a zero. The full length `5` is achievable.

**Implementation notes**

No operation simulation or subsequence dynamic programming is necessary. Read the minimum in one pass, then compare it with the full array length. In the construction above, deleting a different element from the preserved minimum means deleting any other surviving element; there are enough such elements because `m < n`.

**Complete C++20 code**

```cpp
#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, smallest = numeric_limits<int>::max();
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            smallest = min(smallest, x);
        }
        cout << (smallest < n ? n : 0) << '\n';
    }
}
```

**Build and run**

```sh
g++ -std=c++20 -O2 -Wall -Wextra B.cpp -o B
./B < input.txt
```

Save the example input as `input.txt`. The first number is the number of test cases. On Windows, run the corresponding `.exe`.

**Validation**

The C++ source was compiled and checked locally. See [validation details](VALIDATION.md) and the [test script](test_solutions.py). The code block above matches `B.cpp` exactly.
