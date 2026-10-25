#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int count = 0, first = -1, last = -1;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ++count;
                if (first == -1) first = i;
                last = i;
            }
        }

        cout << (count <= 2 ? count - 1 : last - first) << '\n';
    }
    return 0;
}
