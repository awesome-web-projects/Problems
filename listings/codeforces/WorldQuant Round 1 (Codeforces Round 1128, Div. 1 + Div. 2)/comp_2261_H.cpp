#include <bits/stdc++.h>
using namespace std;

bool isParity(int i) {
    return (i & (i - 1)) == 0;
}

void traverse(int v, vector<int>& tree, vector<int>& code,
              int& position, bool writing) {
    if (writing) tree[v] = code[++position];
    else code[++position] = tree[v];

    int size = (int)tree.size() - 1;
    if (2 * v > size) return;
    int first = 2 * v + tree[v];
    traverse(first, tree, code, position, writing);
    traverse(first ^ 1, tree, code, position, writing);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode;
    cin >> mode;
    int t;
    cin >> t;
    while (t--) {
        int n, h;
        string s;
        cin >> n >> h >> s;
        int size = (1 << h) - 1;
        vector<int> code(size + 1, 0), tree(size + 1, 0);

        if (mode == "first") {
            int used = 0, syndrome = 0;
            for (int i = 1; i <= size; ++i) {
                if (!isParity(i) && used < n) {
                    code[i] = s[used++] - '0';
                    if (code[i]) syndrome ^= i;
                }
            }
            for (int bit = 1; bit <= size; bit <<= 1) {
                code[bit] = (syndrome & bit) != 0;
            }

            int position = 0;
            traverse(1, tree, code, position, true);
            string answer;
            answer.reserve(size);
            for (int i = 1; i <= size; ++i) {
                answer += char('0' + tree[i]);
            }
            cout << answer << '\n';
        } else {
            for (int i = 1; i <= size; ++i) tree[i] = s[i - 1] - '0';
            int position = 0;
            traverse(1, tree, code, position, false);

            int syndrome = 0;
            for (int i = 1; i <= size; ++i) {
                if (code[i]) syndrome ^= i;
            }
            if (syndrome != 0) code[syndrome] ^= 1;

            string answer;
            answer.reserve(n);
            for (int i = 1; i <= size && (int)answer.size() < n; ++i) {
                if (!isParity(i)) answer += char('0' + code[i]);
            }
            cout << answer << '\n';
        }
    }
    return 0;
}
