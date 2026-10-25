**C. Edge Addeleting — Complete C++20 Solution**

[Original problem](https://codeforces.com/contest/2277/problem/C) · [C++ source](C.cpp)

**Problem in brief**

Start with a tree on vertices `1..n`. Each operation adds `(1,v)`, creating a cycle, and lets you delete any edge of that cycle, including the new edge. Maximize the final distance from `1` to `n`.

Each test supplies `n m`, the `n-1` edges, then `m` endpoints. Print one maximum distance. Parallel edges created by adding an existing edge are allowed during an operation. The sums of `n` and `m` are each at most `500000`.

**Algorithm and correctness**

Every new edge touches vertex `1`. Consequently, after removing vertex `1`, every remaining edge at every moment is an edge of the original tree.

Let `K` be the component containing `n` when vertex `1` is removed from the original tree. In any final tree, the path from `1` to `n` must begin with an edge `(1,w)` for some `w` in `K`. The rest of that path is forced: it is the original unique path from `w` to `n`. Its length is therefore

`1 + original_distance(w,n)`.

The possible starting vertices `w` are the original neighbor of `1` in `K`, or an operation endpoint belonging to `K`. An endpoint outside `K` cannot help: without vertex `1`, there are no edges connecting its original component to `K`.

Every candidate can actually be achieved. Ignore all operations except the chosen one by deleting their newly added edges. When adding `(1,w)`, delete the original edge from `1` into `K`; the resulting path has the claimed length. The original path itself remains available by ignoring every operation.

So traverse from `n` without entering `1`, recording distances. Initialize the answer to the original distance from `1` to `n`. For each endpoint reached by this traversal, maximize the answer with its recorded distance plus one. The order of operations is irrelevant because one chosen operation suffices.

Time: **O(n+m)**. Extra space: **O(n)**. The traversal is iterative.

**Example input**

```text
3
7 2
1 2
2 3
3 7
2 4
4 5
1 6
6 5
4 1
1 4
1 2
2 3
3
3 1
1 2
2 3
3
```

**Example output**

```text
5
1
2
```

**Worked examples**

These are custom examples.

For the first case, the original tree is:

```text
1 -- 2 -- 3 -- 7
|    |
6    4 -- 5
```

Removing vertex `1` leaves the target component `K={2,3,4,5,7}` and a separate component `{6}`. Distances from target `7` inside `K` are:

| Vertex | 7 | 3 | 2 | 4 | 5 |
|---|---:|---:|---:|---:|---:|
| Distance to 7 | 0 | 1 | 2 | 3 | 4 |

The original answer is `3`. Endpoint `6` is outside `K`, so ignore its operation by deleting the newly added edge. For endpoint `5`, add `(1,5)` and delete `(1,2)`. The new path is `1-5-4-2-3-7`, of length `5`. That is the maximum candidate.

In the second case, target `4` is adjacent to `1`; removing `1` leaves `K={4}`. Endpoint `3` is in another component, so the maximum remains `1`.

In the third case, the original path `1-2-3` has length `2`. Adding `(1,3)` offers length `1`, so retain the original path by deleting the added edge. The answer is `2`.

**Implementation notes**

The traversal deliberately never enters vertex `1`. A distance of `-1` identifies endpoints outside the target's original component. Exactly one vertex in that component was originally adjacent to `1`, which lets the traversal recover the original answer. No recursive DFS is used, so a path of 500000 vertices cannot overflow the call stack.

**Complete C++20 code**

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> graph(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        // Traverse the component of n in the ORIGINAL tree with vertex 1 removed.
        vector<int> distance(n + 1, -1), order{n};
        distance[n] = 0;
        int answer = 0;
        for (size_t i = 0; i < order.size(); ++i) {
            int u = order[i];
            for (int v : graph[u]) {
                if (v == 1) {
                    answer = distance[u] + 1; // The original 1--n distance.
                } else if (distance[v] == -1) {
                    distance[v] = distance[u] + 1;
                    order.push_back(v);
                }
            }
        }
        for (int i = 0, v; i < m; ++i) {
            cin >> v;
            if (distance[v] != -1) answer = max(answer, distance[v] + 1);
        }
        cout << answer << '\n';
    }
}
```

**Build and run**

```sh
g++ -std=c++20 -O2 -Wall -Wextra C.cpp -o C
./C < input.txt
```

Save the example input as `input.txt`. The first number is the number of test cases. On Windows, run the corresponding `.exe`.

**Validation**

The C++ source was compiled and checked locally. See [validation details](VALIDATION.md) and the [test script](test_solutions.py). The code block above matches `C.cpp` exactly.
