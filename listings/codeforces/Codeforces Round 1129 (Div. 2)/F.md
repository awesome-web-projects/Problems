**F. Token Re-Moving — Complete C++20 Solution**

[Original problem](https://codeforces.com/contest/2277/problem/F) · [C++ source](F.cpp)

**Problem in brief**

A tree vertex `i` initially holds `a[i]` tokens. For a chosen root, an operation at `u` gathers every token in `u`'s current subtree onto `u`; its cost is the number gathered, including tokens already at `u`. Perform these operations once each in a given permutation order. Compute the total cost independently for every possible root, modulo `998244353`.

Each case supplies `n`, the `n-1` edges, `n` token counts, and a permutation of the vertices. Print `n` answers in vertex order. The total `n` is at most `500000`.

**Deriving the algorithm**

Running a token simulation separately for each root would be too expensive. Instead, determine which operations contribute to which roots.

**1. Fix a root and characterize one operation**

For a fixed root `r`, examine the operation at vertex `u`.

If a proper ancestor of `u` has already been operated on, the first such operation gathered all tokens from `u`'s subtree into an ancestor outside it. Tokens only move upwards, so that subtree remains empty. The cost at `u` is zero.

Otherwise, no earlier operation moved tokens across the subtree's boundary. Earlier descendant operations merely rearranged tokens within it, while disjoint operations did not affect it. The cost at `u` is therefore the sum of the *initial* tokens in that subtree.

Consequently `u` is eligible to contribute exactly when no vertex on the path from `u` to `r` was operated on earlier. Eligibility does not imply positive cost if the relevant token sum is zero; the same formulas still work.

**2. Reverse time to find all eligible roots**

Activate vertices in order `p[n],p[n-1],...,p[1]`. Just after activating `u`, the active vertices are `u` and vertices operated on later than `u`.

A root `r` is in `u`'s active connected component if and only if its path to `u` contains no earlier vertex. By the previous characterization, this component is exactly the set of roots for which `u` contributes.

Use DSU to maintain components, but also record their history. When activating `u`, make the reconstruction root of every adjacent active component a child of `u`. Then merge these components with `u`.

Different active neighbors belong to different components: connecting them without `u` would create a cycle in the original tree. Thus each activation joins disjoint components, and the history forms a tree on the original `n` vertices. Its root is the last activated vertex `p[1]`.

At the instant `u` is activated, its reconstruction subtree is precisely its active component. Later activations only attach this entire tree under new ancestors and do not change the descendants of `u`. Hence the operations contributing to root `r` are exactly `r` and its ancestors in the reconstruction tree.

**3. Assign one weight to each reconstruction edge**

Let `S` be the total initial tokens. If the answer root equals `u`, the operation at `u` gathers the entire original tree and contributes `S`.

For any other eligible root `r`, let `v` be the original-tree neighbor of `u` in the direction of `r`. Cut edge `(u,v)`, and let `W(u,v)` be the initial token sum on the side containing `v`. With the tree rooted at `r`, the subtree of `u` is the other side, so its contribution is

`S-W(u,v)`.

When activation of `u` attaches component root `c` through edge `(u,v)`, every root in reconstruction subtree `c` lies on that same side. Store `S-W(u,v)` as the reconstruction edge weight from `u` to `c`.

**4. Compute edge-side sums in constant time**

Root the original tree at vertex `1` just for preprocessing. Compute its parent array and initial subtree token sums `sub[u]`.

- If `v=parent[u]`, the side containing `v` has sum `S-sub[u]`. The edge weight is `sub[u]`.
- Otherwise `v` is a child of `u`, and its side has sum `sub[v]`. The edge weight is `S-sub[v]`.

All sums and differences may be reduced modulo `998244353` because the final expression consists only of token-sum additions and subtractions.

**5. Read all answers from reconstruction paths**

For root `r`, its own operation contributes `S`. Each reconstruction ancestor contributes the weight on the next reconstruction edge towards `r`. Therefore

`answer[r] = S + sum(weights on the reconstruction path from p[1] to r)`.

Equivalently, initialize `answer[p[1]]=S`. For each reconstruction child `c` of `u`, set `answer[c]=answer[u]+weight[c]` modulo the modulus.

There is no need for a second DFS: a reconstruction parent is always operated on earlier than its child, so it appears first in the original permutation. One forward pass over that permutation evaluates every answer.

**Correctness argument**

The fixed-root characterization proves that each operation's cost is either zero or its initial subtree sum. Reverse activation identifies exactly the roots for which the latter case applies. The reconstruction tree records those components as subtrees, so its ancestors enumerate exactly the contributing operations for any chosen root. Each stored edge weight equals that ancestor's initial subtree sum for every root in the corresponding child branch. Adding those weights and the root's own contribution `S` therefore gives exactly the total operation cost, for every root independently.

**Complexity**

Original-tree preprocessing and final answer accumulation take O(n) time. Each original edge causes one DSU merge, with union by size and path compression. Total time is **O(n alpha(n))**, where `alpha` is the inverse Ackermann function, and extra space is **O(n)**.


**Example input**

```text
3
1
7
1
3
1 2
2 3
2 3 5
2 1 3
2
1 2
5 13
2 1
```

**Example output**

```text
7
18 10 15
31 18
```

**Worked examples**

These are custom examples.

For a single vertex with seven tokens, its only operation costs seven.

For the second case, the tree is `1-2-3`, initial tokens are `[2,3,5]`, and the order is `[2,1,3]`. Direct simulation gives:

| Root | Cost at vertex 2 | Cost at vertex 1 | Cost at vertex 3 | Total |
|---|---:|---:|---:|---:|
| 1 | 8 | 10 | 0 | 18 |
| 2 | 10 | 0 | 0 | 10 |
| 3 | 5 | 0 | 10 | 15 |

When the root is `1`, the first operation moves the three tokens at `2` and five tokens at `3` to vertex `2`. Vertex `1` then gathers all ten tokens. Vertex `3` is empty when its operation occurs.

The reverse activation order is `[3,1,2]`. Vertices `3` and `1` initially form separate components. Activating `2` attaches both components below reconstruction root `2`:

```text
        2                 answer[2] = 10
       / \
   +8 /   \ +5
     1     3              answer[1] = 18, answer[3] = 15
```

The weight towards vertex `1` is `8`: cutting original edge `(2,1)` leaves `3+5` tokens on the side containing `2`. The weight towards vertex `3` is `5`: cutting `(2,3)` leaves `2+3` tokens on the side containing `2`.

In the last case, rooting at `1` makes the operation at `2` cost `13`, then the operation at `1` cost `18`, totaling `31`. Rooting at `2` gathers all `18` tokens immediately, so the later operation costs zero and the total is `18`.

**Implementation notes**

The original-tree parent array and reconstruction parent array have different roles. The first computes token sums on each side of an original edge. The second accumulates contributions between answer roots.

DSU representatives are selected by union by size, so they need not be the desired reconstruction roots. `top[find(v)]` stores the reconstruction root separately. After merging into the newly activated vertex `u`, this field is set to `u`.

The edge weight must use original token-side sums, not the sum of the currently active DSU component: earlier vertices can still hold tokens that the operation gathers for a suitable root. All traversals and DSU searches are iterative to support paths of length 500000.

**Complete C++20 code**

```cpp
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using int64 = long long;
constexpr int64 MOD = 998244353;

struct DSU {
    vector<int> parent, size, top;
    explicit DSU(int n) : parent(n + 1), size(n + 1, 1), top(n + 1) {
        iota(parent.begin(), parent.end(), 0);
        iota(top.begin(), top.end(), 0);
    }
    int find(int u) {
        int root = u;
        while (root != parent[root]) root = parent[root];
        while (u != root) {
            int next = parent[u];
            parent[u] = root;
            u = next;
        }
        return root;
    }
    void unite(int u, int v, int new_top) {
        u = find(u);
        v = find(v);
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;
        size[u] += size[v];
        top[u] = new_top;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> graph(n + 1);
        for (int i = 1, u, v; i < n; ++i) {
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int64> subtree(n + 1);
        for (int u = 1; u <= n; ++u) cin >> subtree[u];
        vector<int> permutation(n);
        for (int& u : permutation) cin >> u;

        vector<int> parent(n + 1), traversal{1};
        for (size_t i = 0; i < traversal.size(); ++i) {
            int u = traversal[i];
            for (int v : graph[u]) if (v != parent[u]) {
                parent[v] = u;
                traversal.push_back(v);
            }
        }
        for (int i = n - 1; i > 0; --i) {
            int u = traversal[i];
            subtree[parent[u]] = (subtree[parent[u]] + subtree[u]) % MOD;
        }
        int64 total = subtree[1];
        DSU dsu(n);
        vector<bool> active(n + 1);
        vector<int> reconstruction_parent(n + 1);
        vector<int64> weight(n + 1), answer(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            int u = permutation[i];
            active[u] = true;
            for (int v : graph[u]) if (active[v]) {
                int child = dsu.top[dsu.find(v)];
                reconstruction_parent[child] = u;
                weight[child] = (parent[u] == v) ? subtree[u]
                    : (total - subtree[v] + MOD) % MOD;
                dsu.unite(u, v, u);
            }
        }
        answer[permutation[0]] = total;
        // Reconstruction parents precede children in the original permutation.
        for (int i = 1; i < n; ++i) {
            int u = permutation[i];
            answer[u] = (answer[reconstruction_parent[u]] + weight[u]) % MOD;
        }
        for (int u = 1; u <= n; ++u) cout << answer[u] << (u == n ? '\n' : ' ');
    }
}
```

**Build and run**

```sh
g++ -std=c++20 -O2 -Wall -Wextra F.cpp -o F
./F < input.txt
```

Save the example input as `input.txt`. The first number is the number of test cases. On Windows, run the corresponding `.exe`.

**Validation**

The C++ source was compiled and checked locally. See [validation details](VALIDATION.md) and the [test script](test_solutions.py). The code block above matches `F.cpp` exactly.

The [official editorial](https://codeforces.me/blog/entry/158113) was consulted to cross-check the underlying approach. The implementation, worked examples, and expanded arguments are included here for independent study.
