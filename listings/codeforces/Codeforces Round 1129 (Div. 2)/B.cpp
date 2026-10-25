#include <algorithm>
#include <iostream>
#include <limits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, smallest = numeric_limits<int>::max();
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            smallest = min(smallest, x);
        }
        cout << (smallest < n ? n : 0) << '\n';
    }
}
