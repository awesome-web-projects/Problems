// https://codeforces.com/contest/1744/my
// fastest solution
#include <bits/stdc++.h>
using namespace std;

int main(void) {

    int T = 0, N = 0, q = 0, temp = 0;
    long long int ec = 0, oc = 0, sum = 0;
    long long int q_1 = 0, q_2 = 0;

    std::cin >> T;
    
    while(T--) {
        std::cin >> N >> q;

        ec = 0; oc = 0; sum = 0;
        for (auto j = 0; j < N; j++) {
            std::cin >> temp;
            (temp&1LL) == 0 ? ec++ : oc++;
            sum += temp;
        } 

        while(q--) {
            std::cin >> q_1 >> q_2;
            bool flag = (q_2&1LL) == 1 ? 1 : 0;

            if ((q_1 == 0) && (q_2 != 0)) {
                sum += q_2 * ec;
                // add an odd number to even numbers.
                if (flag) {
                    ec = 0;
                    oc = N;
                }
            } else {
                sum += q_2 * oc;
                // add an even number to odd numbers.
                if (flag) {
                    ec = N;
                    oc = 0;
                }
            }
            std::cout << sum << "\n";
        }
    }
    
    return 0;
}
