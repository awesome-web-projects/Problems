#include <bits/stdc++.h>
using namespace std;

constexpr int B = 25;
static int frequency[1 << B];

struct Event {
    int key;  // A negative key ~x means subtract frequency[x].
    int next;
};

long long solve(const vector<int>& a) {
    const int n = (int)a.size();
    int allBits = 0;
    for (int x : a) allBits |= x;
    if (allBits == 0) return 0;

    vector<array<int, B>> nextZero(n + 1);
    vector<array<unsigned char, B>> order(n);
    nextZero[n].fill(n);

    for (int i = n - 1; i >= 0; --i) {
        nextZero[i] = nextZero[i + 1];
        for (int b = 0; b < B; ++b) {
            if (((a[i] >> b) & 1) == 0) nextZero[i][b] = i;
            order[i][b] = (unsigned char)b;
        }
        sort(order[i].begin(), order[i].end(),
             [&](unsigned char x, unsigned char y) {
                 return nextZero[i][x] < nextZero[i][y];
             });
    }

    vector<int> head(n, -1);
    vector<Event> events;
    events.reserve((size_t)2 * n * B);
    long long answer = 0;

    for (int b = 0; b < B; ++b) {
        if (((allBits >> b) & 1) == 0) continue;
        fill(head.begin(), head.end(), -1);
        events.clear();

        auto addEvent = [&](int at, int key) {
            events.push_back({key, head[at]});
            head[at] = (int)events.size() - 1;
        };

        int suffix = 0;
        for (int i = n - 1; i >= 0; --i) {
            suffix ^= a[i];
            if (((a[i] >> b) & 1) == 0) continue;

            int mask = a[i];
            int left = i;
            int j = 0;

            while (j < B) {
                int right = nextZero[i][order[i][j]];
                int removed = 0;

                while (j < B && nextZero[i][order[i][j]] == right) {
                    int bit = order[i][j++];
                    if (bit >= b) removed |= 1 << bit;
                }

                if (removed == 0 || right == i) continue;

                // For endpoints r in [left, right), AND >> b is fixed.
                int key = (suffix ^ mask) >> b;
                addEvent(left, key);
                if (right < n) addEvent(right, ~key);

                mask &= ~removed;
                left = right;
                if (((mask >> b) & 1) == 0) break;
            }
        }

        long long count = 0;
        suffix = 0;
        for (int i = n - 1; i >= 0; --i) {
            ++frequency[suffix >> b];
            suffix ^= a[i];

            for (int e = head[i]; e != -1; e = events[e].next) {
                int key = events[e].key;
                if (key >= 0) count += frequency[key];
                else count -= frequency[~key];
            }
        }

        answer += count * (1LL << b);

        // Clear only table entries touched in this sweep.
        suffix = 0;
        for (int i = n - 1; i >= 0; --i) {
            frequency[suffix >> b] = 0;
            suffix ^= a[i];
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        cout << solve(a) << '\n';
    }
    return 0;
}
