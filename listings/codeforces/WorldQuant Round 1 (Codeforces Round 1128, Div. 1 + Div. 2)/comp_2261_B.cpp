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

        long long minimum = LLONG_MAX, maximum = 0;
        for (int i = 0; i < n; ++i) {
            long long x;
            cin >> x;
            minimum = min(minimum, x);
            maximum = max(maximum, x);
        }

        long long difference = minimum ^ maximum;
        long long mask = 0;
        while (difference > 0) {
            mask = (mask << 1) | 1LL;
            difference >>= 1;
        }

        cout << (maximum | mask) << '\n';
    }
    return 0;
}
