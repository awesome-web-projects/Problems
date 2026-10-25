#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int odd = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            odd += x & 1;
        }

        bool losing = (n == 2 && odd == 1) ||
                      (n == 3 && odd == 3);
        cout << (losing ? "Larpity" : "Moggity") << '\n';
    }
    return 0;
}
