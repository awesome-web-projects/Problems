#include <algorithm>
#include <array>
#include <bit>
#include <iostream>
using namespace std;
using int64 = long long;
constexpr int64 MOD = 998244353;
constexpr int64 INV2 = (MOD + 1) / 2;

int highest_bit(int64 n) {
    return static_cast<int>(bit_width(static_cast<unsigned long long>(n))) - 1;
}

int64 minimum_operations(int64 n) {
    static constexpr int base[] = {0, 1, 3, 2};
    if (n < 4) return base[n];
    int k = highest_bit(n);
    int64 power = 1LL << k;
    return min(minimum_operations(n - power + 2) + k + 1,
               2 * power - n + k);
}

struct PrefixSolver {
    array<int64, 60> cutoff{}, before{};

    int64 prefix(int64 n) const {
        if (n < 0) return 0;
        static constexpr int small[] = {0, 1, 4, 6};
        if (n < 4) return small[n];
        int k = highest_bit(n);
        int64 power = 1LL << k;
        int64 end = min(n, cutoff[k]);
        int64 count = end - power + 1;
        int64 result = (before[k] + prefix(end - power + 2) - 1 + MOD
                      + (count % MOD) * (k + 1)) % MOD;
        // Beyond cutoff[k], f is an arithmetic progression with difference -1.
        int64 tail = n - end;
        int64 first = 2 * power + k - end - 1;
        int64 last = 2 * power + k - n;
        result = (result + ((first + last) % MOD) * (tail % MOD) % MOD * INV2) % MOD;
        return result;
    }

    PrefixSolver() {
        for (int k = 2; k < 60; ++k) {
            int64 power = 1LL << k;
            // h(m) = m + f(m) is nondecreasing. Find its last valid m.
            int64 low = 2, high = power - 1, position = 2;
            while (low <= high) {
                int64 middle = low + (high - low) / 2;
                if (middle + minimum_operations(middle) <= power + 1) {
                    position = middle;
                    low = middle + 1;
                } else {
                    high = middle - 1;
                }
            }
            cutoff[k] = power + position - 2;
            before[k] = prefix(power - 1);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    PrefixSolver solver;
    int t;
    cin >> t;
    while (t--) {
        int64 l, r;
        cin >> l >> r;
        cout << (solver.prefix(r) - solver.prefix(l - 1) + MOD) % MOD << '\n';
    }
}
