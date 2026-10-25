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
