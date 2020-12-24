/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/CSUB 

#include <bits/stdc++.h>
using namespace std;

#define forl(i, A, N) for(auto i = A; i < N; ++i)

template<class T>
struct Compare{
    bool operator() (const T& _lhs, const T& _rhs){
        return true;
    }
};

void solve_problems();
std::vector<string> remove_split_spaces(std::string str) {
    std::vector<string> amp;
    std::string::iterator iter = std::unique(str.begin(), str.end(), [](char a, char b) { 
        return a == b && a == ' ' ;
    });
    str.erase(iter, str.end());
    while(str[str.length() - 1] == ' ') {
        str.pop_back();
    }
    auto delimiter = ' ';
    size_t i = 0, pos = str.find(delimiter);
    while(pos != string::npos) {
        amp.push_back(str.substr(i, pos - i));
        i = pos + 1;
        pos = str.find(delimiter, i);
    }
    amp.push_back(str.substr(i, pos));
    return amp;
}

template<class T>
void pl(T& cont)
{
	for(typename T::iterator itr = cont.begin(); itr != cont.end(); itr++){
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
}

/* Main */
int main(int argc, char* argv[], char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    solve_problems();
    return 0;
}

void solve_problems()
{   
    char ch;
    unsigned long int T = 0, N = 0;
    long long int A = 0, B = 0, K = 0, M = 0;
    std::cin >> T;
    while(T--) {
        std::cin >> N;
        std::vector<long long int> __input(N, 0);
        std::deque<long long int> __dq(N, 0);
        forl(i, 0, N) {
            std::cin >> ch;
            __input[i] = ch - '0';
        }
        long long int sum = 0, count_of_ones = 0;
        forl(i, 0, N) {
            if(__input[i] == 1){
                ++count_of_ones;
                sum  = sum + count_of_ones;
            }
        }
        std::cout << sum << std::endl;
    }
}
