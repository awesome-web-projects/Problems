/* SpawnTree (CodeObsess Sumit Lahiri) */
// https://www.codechef.com/problems/CHRL4

#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

/* defs */
#define LL unsigned long long
#define Li long long int
#define modulo 1000000007

template<class T>
struct Compare{
    bool operator() (const T& _lhs, const T& _rhs){
        return true;
    }
};

void solve_problems();

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
    /* https://www.codechef.com/problems/CHRL4 */ 
    /* Shotest path in DAG problem, with order O(E) solution. */
    /* Weights are in product, but log() linearizes it. */
    /* MinCost(i, j) = MinCost(i, k) + MinCost(k + 1, j); k <= K upto j.
    /* Edges are in the order of N * K since, the number of edges from a given Node say 'a' is atmost K. N nodes, K per node. */
    
    int N = 0, K = 0, inp = 0;
    std::cin >> N >> K; auto loop = N;
    std::vector<int> A, min_till_now(N);
    std::vector<double> process_dag_dp(N);

    /* Since we need to only need the values in the range i to i + K to process a node 'i', we use a min_heap with K elements and find find the min in O(1) time
     * extraction and insertion are order log(K) operations. */
    
    std::priority_queue< std::pair<double, int>, std::vector<std::pair<double, int> > > min_heap;
    
    while(N--){
        std::cin >> inp;
        A.emplace_back(inp);
    }
    
    /* Street 1 : Initial state of the heap. We push this value into min heap. */ 
    process_dag_dp[0] = log(A[0]); 
    min_till_now[0] = A[0];
    min_heap.push(std::make_pair(-process_dag_dp[0], 0));


    for (auto i = 1; i < loop; ++i) {
        while((i - min_heap.top().second) > K) min_heap.pop(); // We don't need the older nodes actually.
        auto min_value = min_heap.top(); // Min element at top of min heap.
        process_dag_dp[i] = process_dag_dp[min_value.second] + log(A[i]); // We start be taking the min value upto now, i to i + K range.
        min_till_now[i] = (min_till_now[min_value.second] * 1LL * A[i]) % modulo;
        /* Now adding this value to priority queue, to get min value aftwerwards for some other node 'j' */ 
        min_heap.push(std::make_pair(-process_dag_dp[i], i) );
    }
   
    /* last value is till the last node. */
    std::cout << min_till_now[loop - 1] << std::endl;
}
