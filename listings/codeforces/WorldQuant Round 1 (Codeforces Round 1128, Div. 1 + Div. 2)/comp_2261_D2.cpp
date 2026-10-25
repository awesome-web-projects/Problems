#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
using Hash = pair<ull, ull>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    mt19937_64 rng(
        chrono::steady_clock::now().time_since_epoch().count()
    );

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<Hash> difference(n + 2, {0, 0});
        for (int i = 0; i < m; ++i) {
            int l, r;
            cin >> l >> r;
            Hash h = {rng(), rng()};
            difference[l].first ^= h.first;
            difference[l].second ^= h.second;
            difference[r + 1].first ^= h.first;
            difference[r + 1].second ^= h.second;
        }

        map<Hash, int> ids;
        vector<int> label(n + 1), last(n, 0), cuts;
        cuts.reserve(n);
        Hash current = {0, 0};
        int colors = 0, lastCut = 0;

        for (int i = 1; i <= n; ++i) {
            current.first ^= difference[i].first;
            current.second ^= difference[i].second;
            auto [it, inserted] = ids.emplace(current, colors);
            if (inserted) ++colors;

            int color = it->second;
            label[i] = color;
            if (last[color] > lastCut) {
                cuts.push_back(i - 1);
                lastCut = i - 1;
            }
            last[color] = i;
        }

        int q = (int)cuts.size();
        if (q == 0) {
            cout << 0 << '\n';
            continue;
        }

        vector<int> boundaries = cuts;
        if (q & 1) {
            boundaries.insert(boundaries.begin(), 0);
        } else {
            vector<char> inFirst(colors, false);
            for (int i = 1; i <= cuts.front(); ++i) {
                inFirst[label[i]] = true;
            }

            bool common = false;
            for (int i = cuts.back() + 1; i <= n; ++i) {
                if (inFirst[label[i]]) {
                    common = true;
                    break;
                }
            }
            if (common) {
                boundaries.insert(boundaries.begin(), 0);
                boundaries.push_back(n);
            }
        }

        int k = (int)boundaries.size() / 2;
        cout << k << '\n';
        for (int i = 0; i < k; ++i) {
            cout << boundaries[i] + 1 << ' '
                 << boundaries[i + k] << '\n';
        }
    }
    return 0;
}
