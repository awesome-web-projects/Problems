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
