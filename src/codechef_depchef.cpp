// https://www.codechef.com/problems/DEPCHEF
/* SpawnTree (CodeObsess Sumit Lahiri) */

#include <bits/stdc++.h>
using namespace std;

/* Trace for recursions. */
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    std::cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

/* defs */
#define LL unsigned long long
#define Li long long int

void solve_problems_for_life();

template<class T>
void _PrinT(T& cont)
{
	for(typename T::iterator itr = cont.begin(); itr != cont.end(); itr++){
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
}

/* Main */
int main(int argc, char* argv[], char* envp[])
{
    auto start = std::chrono::system_clock::now();
    // ios::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    solve_problems_for_life();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end); 
    // std::cerr << std::fixed << "Elapsed time : " << elapsed_seconds.count() << "s, Program Executed Successfully. Press Ctrl + S to re-compile. (Output Synced). " << "Finished computation at : " << std::ctime(&end_time);
    return 0;
}

void solve_problems_for_life()
{
    int T = 0;
    std::cin >> T;
    while(T--){
        int N = 0, inp = 0, max = -1;
        int A[100] = {0};
        int D[100] = {0};
        std::cin >> N;
        for(auto i = 0; i < N; i++){
            D[i] = 0;
            A[i] = 0;
        }
        for(auto i = 0; i < N; i++){
            std::cin >> inp;
            A[i] = (inp);
        }
        for(auto i = 0; i < N; i++){
            std::cin >> inp;
            D[i] = (inp);
        }
        for(auto i = 0; i < N; i++){
            if(((D[i] - (A[((i - 1 + N) % N)] + A[((i + 1 + N) % N)]))>0) && (D[i] > max)){
                max = D[i];
            }
        }
        std::cout << max << "\n";
    }
}
