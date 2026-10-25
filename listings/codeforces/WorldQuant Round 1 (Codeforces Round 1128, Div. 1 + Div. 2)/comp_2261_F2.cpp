#include <bits/stdc++.h>
using namespace std;

struct Step {
    char direction;
    int zeros;
};

vector<string> encode(int n, int r, int c) {
    vector<Step> steps;
    auto add = [&](char direction, int times, int zeros) {
        while (times--) steps.push_back({direction, zeros});
    };

    int up = min(r - 1, n - 3);
    int p = r - up;
    add('U', up, 3);
    add('D', n - 3 - up, 2);

    int finalZeros = 0;
    if (p == 3) {
        add('R', n - c, 3);
        add('L', c - 1, 2);
        add('U', 1, 2);
        add('U', 1, 1);
    } else {
        add('L', c - 1, 2);
        add('R', n - c, 1);
        add('D', 1, 1);
        if (p == 1) {
            add('D', 1, 0);
        } else {
            add('U', 1, 1);
            finalZeros = 1;
        }
    }

    vector<string> grid(n, string(n, '1'));
    int top = 0, bottom = n - 1;
    int left = 0, right = n - 1;

    for (int i = 0; i < (int)steps.size(); ++i) {
        int after = i + 1 < (int)steps.size()
                  ? steps[i + 1].zeros : finalZeros;
        int drop = steps[i].zeros - after;
        char d = steps[i].direction;

        // Put disappearing zeros into the strip deleted at this step.
        if (d == 'U' || d == 'D') {
            int row = d == 'U' ? top : bottom;
            for (int j = 0; j < drop; ++j) grid[row][left + j] = '0';
            if (d == 'U') ++top;
            else --bottom;
        } else {
            int col = d == 'L' ? left : right;
            for (int j = 0; j < drop; ++j) grid[top + j][col] = '0';
            if (d == 'L') ++left;
            else --right;
        }
    }

    if (finalZeros) grid[r - 1][c - 1] = '0';
    return grid;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            vector<string> grid = encode(n, r, c);
            for (const string& row : grid) cout << row << '\n';
        }
    }

    string actions(n * n + 1, 'U');
    actions[2] = 'D';
    for (int w = 2; w <= n; ++w) {
        actions[3 * w - 3] = 'R';
        actions[3 * w - 2] = 'L';
        actions[3 * w - 1] = 'R';
    }
    for (int h = 4; h <= n; ++h) {
        actions[n * h - 3] = 'U';
        actions[n * h - 2] = 'D';
    }
    cout << actions << '\n';
    return 0;
}
