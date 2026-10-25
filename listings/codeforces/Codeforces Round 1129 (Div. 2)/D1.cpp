#include <algorithm>
#include <bit>
#include <iostream>
using namespace std;
using int64 = long long;
constexpr int64 MOD = 998244353;

int64 minimum_operations(int64 n) {
    static constexpr int base[] = {0, 1, 3, 2};
    if (n < 4) return base[n];
    int k = static_cast<int>(bit_width(static_cast<unsigned long long>(n))) - 1;
    int64 power = 1LL << k;
    return min(minimum_operations(n - power + 2) + k + 1,
               2 * power - n + k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int64 l, r, answer = 0;
        cin >> l >> r;
        for (int64 n = l; n <= r; ++n) {
            answer += minimum_operations(n);
            if (answer >= MOD) answer -= MOD;
        }
        cout << answer << '\n';
    }
}
