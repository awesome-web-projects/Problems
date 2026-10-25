#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> frequency(n + 1);
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            ++frequency[x];
        }
        int answer = 0, available = 0;
        for (int value = 0; value <= n; ++value) {
            available += frequency[value];
            if (frequency[value] == 0 || available < k) break;
            available -= k;
            ++answer;
        }
        cout << answer << '\n';
    }
}
