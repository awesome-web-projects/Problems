**E. Tree Guessing — Interactive — Complete C++20 Solution**

[Original problem](https://codeforces.com/contest/2277/problem/E) · [C++ source](E.cpp)

**Problem in brief**

A hidden tree has `n` labeled vertices. A query chooses a starting vertex `x` and a permutation of labels `p[1..n]`. The response is the sum, over all vertices `v`, of the maximum label on the path from `v` to `x`, including both endpoints. Recover all edges in at most `2n-2` queries. Here `2 <= n <= 500`.

This is an interactive program. It prints queries and reads replies from a judge; it does not read the hidden edges as ordinary input.

**Deriving the query strategy**

Root the hidden tree at vertex `1`. The plan is to first learn every subtree size, then insert vertices in an order in which each parent is already known.

**Phase 1: one query for each subtree size**

For each `u != 1`, query from `x=1` with label `p[1]=n-1` and `p[u]=n`. Assign the other labels `1..n-2` in any order.

Every path ends at `1`, so its maximum is at least `n-1`. It is `n` exactly when the path also visits `u`, which happens precisely for vertices in the subtree of `u`. Therefore

`reply = n(n-1) + size[u]`.

Subtract the fixed term to recover `size[u]`. The root's size is already `n`. This uses `n-1` queries.

Sort vertices by decreasing subtree size, breaking ties arbitrarily. A proper ancestor has a strictly larger subtree than each descendant, so every ancestor appears earlier. In particular, all placed vertices form an ancestor-closed, connected part of the hidden tree.

**Phase 2: determine one parent per query**

Use one-based positions in this sorted order. Suppose the current vertex `u` is at position `i`; there are `i-1` known vertices. Its unknown parent `f` is among them.

Construct a permutation as follows:

1. Give `u` label `1`.
2. Traverse the known tree in breadth-first order and assign labels `2,3,...,i`.
3. Give each later vertex at sorted position `j>i` the label `j`.

These are exactly the labels `1..n`, each used once. Query from `x=u`.

Consider a later vertex `w`, at position `j`. Every other vertex on the path from `w` to `u` is an ancestor of `w` or an ancestor of `u`. Proper ancestors of `w` have positions below `j`; ancestors of `u` are already known. Their labels are all below `j`. Thus `w` contributes exactly its own label `j`, independent of its unknown parent. The total from later vertices is the known constant

`(i+1 + n)(n-i)/2`.

Vertex `u` itself contributes `1`.

For a known vertex `v`, its path to `u` consists of the known path from `v` to `f`, followed by the edge to `u`. Along the known path, no vertex is deeper than the deeper of its endpoints. Breadth-first labels increase with depth, and the only vertices at the maximum endpoint depth on this path are endpoints. Thus the path's maximum is `max(p[v],p[f])`. Label `1` at `u` cannot increase it.

If `z=p[f]`, the contribution from all known vertices is

`H(z) = sum(max(q,z), q=2..i)`

`     = z(z-1) + (z+1+i)(i-z)/2`.

There are `z-1` labels in `2..z`, each contributing `z`; larger labels contribute themselves. Subtract the later-vertex constant and `1` from the response, then test the known vertices' labels against this expression.

**Why the parent is determined uniquely**

For `2 <= z < i`, increasing the parent label from `z` to `z+1` increases exactly `z-1` terms in `H` by one. Hence

`H(z+1)-H(z)=z-1>0`.

Every possible parent therefore has a distinct predicted response. The true parent matches one of them, so each query identifies exactly one edge. Starting with the root, induction reconstructs the entire tree.

Phase 2 uses another `n-1` queries: exactly **2n-2** overall. Label construction, BFS, and candidate testing each take O(n) time per inserted vertex. Total local time is **O(n^2)** and extra space is **O(n)**.


**Worked interactive example**

Take the custom hidden tree with edges `(1,2), (2,3), (1,4)`:

```text
    1
   / \
  2   4
  |
  3
```

The root's subtree size is four. Phase 1 gives:

| Query root `x` | Permutation `[p1,p2,p3,p4]` | Judge reply | Derived size |
|---|---|---:|---|
| 1 | `[3,4,1,2]` | 14 | `size[2]=14-12=2` |
| 1 | `[3,1,4,2]` | 13 | `size[3]=13-12=1` |
| 1 | `[3,1,2,4]` | 13 | `size[4]=13-12=1` |

Use sorted order `[1,2,3,4]`. The second phase is:

| Current vertex | Query labels | Reply | Fixed contribution removed | Known contribution | Parent |
|---|---|---:|---:|---:|---|
| 2 | `[2,1,3,4]` | 10 | `1+3+4=8` | 2 | 1 |
| 3 | `[2,3,1,4]` | 11 | `1+4=5` | 6 | 2 |
| 4 | `[2,3,4,1]` | 10 | `1` | 9 | 1 |

For instance, while attaching vertex `3`, candidate parent label `2` predicts `H(2)=2+3=5`, while candidate parent label `3` predicts `H(3)=3+3=6`. The observed contribution is six, so the parent is vertex `2`.

The complete exchange is shown below. Lines beginning with `>` are sent by the solution; lines beginning with `<` are sent by the judge. These direction markers are explanatory and are not printed by the program.

```text
< 1
< 4
> ? 1 3 4 1 2
< 14
> ? 1 3 1 4 2
< 13
> ? 1 3 1 2 4
< 13
> ? 2 2 1 3 4
< 10
> ? 3 2 3 1 4
< 11
> ? 4 2 3 4 1
< 10
> !
> 1 2
> 2 3
> 1 4
```

There are six queries, exactly `2*4-2`. To test other hidden trees, use `test_solutions.py`, which supplies replies and checks recovered edges. Do not feed this transcript or an edge list to the program as an ordinary noninteractive sample.


**Implementation notes**

In `E.cpp`, `index` is the number of already placed vertices. The current vertex has one-based position `i=index+1`; known labels are `2..i`. The vector `children` stores the reconstructed tree, and `bfs` provides an order whose labels increase along every ancestor-to-descendant path.

The `query` function flushes using `endl`, reads exactly one response, and exits immediately on EOF or `-1`. After printing `!` and the `n-1` edges, the program flushes again. No verdict is read between test cases because the original protocol proceeds directly to the next case.

**Complete C++20 code**

```cpp
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using int64 = long long;

int64 query(int x, const vector<int>& label) {
    cout << "? " << x;
    for (size_t v = 1; v < label.size(); ++v) cout << ' ' << label[v];
    cout << endl; // Flush every query.
    int64 reply;
    if (!(cin >> reply) || reply == -1) exit(0);
    return reply;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        if (!(cin >> n) || n == -1) return 0;
        vector<int> size(n + 1), label(n + 1), order(n);
        size[1] = n;
        iota(order.begin(), order.end(), 1);
        for (int u = 2; u <= n; ++u) {
            label[1] = n - 1;
            label[u] = n;
            int next = 1;
            for (int v = 2; v <= n; ++v) if (v != u) label[v] = next++;
            size[u] = static_cast<int>(query(1, label) - 1LL * n * (n - 1));
        }
        sort(order.begin(), order.end(), [&](int u, int v) {
            if (size[u] != size[v]) return size[u] > size[v];
            return u < v;
        });
        vector<vector<int>> children(n + 1);
        vector<pair<int, int>> edges;
        for (int index = 1; index < n; ++index) {
            int u = order[index];
            vector<int> bfs{1};
            for (size_t j = 0; j < bfs.size(); ++j) {
                int v = bfs[j];
                for (int child : children[v]) bfs.push_back(child);
            }
            for (int j = 0; j < index; ++j) label[bfs[j]] = j + 2;
            label[u] = 1;
            for (int j = index + 1; j < n; ++j) label[order[j]] = j + 1;

            int64 reply = query(u, label) - 1;
            int64 unknown_count = n - index - 1;
            reply -= 1LL * (index + 2 + n) * unknown_count / 2;
            int last_label = index + 1;
            for (int j = 0; j < index; ++j) {
                int z = label[bfs[j]];
                int64 expected = 1LL * z * (z - 1)
                    + 1LL * (z + 1 + last_label) * (last_label - z) / 2;
                if (expected == reply) {
                    children[bfs[j]].push_back(u);
                    edges.emplace_back(bfs[j], u);
                    break;
                }
            }
        }
        cout << "!\n";
        for (auto [u, v] : edges) cout << u << ' ' << v << '\n';
        cout << flush;
    }
}
```

**Build and run**

```sh
g++ -std=c++20 -O2 -Wall -Wextra E.cpp -o E
python test_solutions.py --bin-dir .
```

Build all seven executable files before running the supplied test script. It includes a local interactive judge for E, including permutation checks, query-limit checks, and edge verification.

**Validation**

The C++ source was compiled and checked locally. See [validation details](VALIDATION.md) and the [test script](test_solutions.py). The code block above matches `E.cpp` exactly.

The [official editorial](https://codeforces.me/blog/entry/158113) was consulted to cross-check the underlying approach. The implementation, worked examples, and expanded arguments are included here for independent study.
