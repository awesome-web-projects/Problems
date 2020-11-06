/* SpawnTree (CodeObsess Sumit Lahiri) */

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/trie_policy.hpp>
#include <ext/pb_ds/tag_and_trait.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using namespace __gnu_pbds;

/* defs */
#define LL unsigned long long
#define Ld long double
#define itn int
// constexpr LL MOD = 18446744073709551615;

template<class T>
void print(T& cont)
{
	for(typename T::iterator itr = cont.begin(); itr != cont.end(); itr++){
		std::cout << *(itr) << " ";
	}
	std::cout << std::endl;
}

/* Main */
int main(int argc, char* argv[], char* envp[])
{
    // freopen("input.in", "r+", stdin);
    // freopen("output.txt", "w+", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    std::stringstream buffer;
    std::string input = "", output = " ";
    int T = 0; 
    LL N = 0, C = 0;

    std::cin >> T;
	for(auto t = 0; t < T; ++t) {
	   	std::cin >> N >> C;
    	LL sum = 0;
    	while(N --> 0) {
    		LL count = 0;
    		std::cin >> count;
    		sum += count;
    	}
    	std::cout << ((sum <= C)?"Yes":"No") << std::endl;
    }  	
   
    return 0;
}
