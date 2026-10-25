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
