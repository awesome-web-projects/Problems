#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;  // m is guaranteed to be zero in D1.

        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        int k = (n + 1) / 2;
        cout << k << '\n';
        for (int i = 1; i <= k; ++i) {
            cout << i << ' ' << i + k - 1 << '\n';
        }
    }
    return 0;
}
