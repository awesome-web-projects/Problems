#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s;
        int m = n / 2;

        vector<int> c;
        c.reserve(m + 1);
        c.push_back(0);
        int run = 0;
        for (char ch : s) {
            if (ch == '(') {
                ++run;
            } else {
                c.push_back(run);
                run = 0;
            }
        }

        vector<int> prefix(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            prefix[i] = prefix[i - 1] + c[i] - 1;
        }

        int answer = 0, prefixOpen = 0;
        deque<int> candidates;
        for (int r = 1; r <= m; ++r) {
            prefixOpen += c[r];
            if (r - 1 <= k) {
                answer = max(answer, min(m, prefixOpen + k - (r - 1)));
            }

            int p = r - 1;
            while (!candidates.empty() &&
                   prefix[candidates.back()] >= prefix[p]) {
                candidates.pop_back();
            }
            candidates.push_back(p);
            while (candidates.front() < r - k - 1) {
                candidates.pop_front();
            }
            answer = max(answer, prefix[r] - prefix[candidates.front()] + 1);
        }
        cout << answer << '\n';
    }
    return 0;
}
