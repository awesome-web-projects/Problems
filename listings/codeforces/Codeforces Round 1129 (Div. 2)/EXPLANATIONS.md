**Codeforces 2277 — seven C++20 solutions**

Each `.cpp` file is an independent program using only standard C++20 headers. The explanations below develop the observations, justify the algorithms, and give their costs. Let `V = 10^18` for D1/D2. All modular answers use `998244353`.

**1. A — Subset Selecting** · [Statement](https://codeforces.com/contest/2277/problem/A) · `A.cpp`

To obtain a MEX of at least `q`, we need groups whose maxima are `0,1,...,q-1`. Extra groups do not help. We can also restrict every useful group to exactly `k` elements: keep one occurrence of its maximum and any `k-1` other elements.

This suggests processing the required maxima in increasing order. Let `available` count unused elements whose values are at most the current maximum `v`.

Add `frequency[v]` to `available`. A group with maximum `v` exists precisely when both conditions hold:

- `frequency[v] > 0`, so the maximum itself is present;
- `available >= k`, so there are enough elements for the group.

On success, consume `k` elements. Otherwise, stop and return `v`.

Why can we ignore which particular elements were consumed? Every earlier group has maximum smaller than `v`, so no occurrence of `v` has been consumed. All other available elements are interchangeable as fillers: every later maximum permits all of them. Using exactly `k` elements also leaves as many fillers as possible for later groups. Thus a failure cannot be repaired by changing earlier choices, and every successful step is safe.

For example, with `k=2` and `[0,0,0,1,1,2]`, choose `{0,0}`, `{0,1}`, and `{1,2}`. Their maxima are `0,1,2`, giving MEX `3`.

Time: **O(n)**. Extra space: **O(n)**.

**2. B — Sequence Decreasing** · [Statement](https://codeforces.com/contest/2277/problem/B) · `B.cpp`

The answer is always either the entire length `n` or zero:

`answer = n` if `min(a) < n`; otherwise `answer = 0`.

Here is the construction behind that surprisingly short condition. If a zero already exists, keep it and delete every positive element by operating on that element alone. A singleton operation can delete a positive element regardless of its magnitude.

Otherwise let the minimum value be `m`, with `1 <= m < n`, and select an occurrence of it to preserve. Operate on the whole remaining array `m` times, each time deleting a different element from the selected minimum. Before the last operation, all remaining values are positive: each started at least `m`, and fewer than `m` decrements have occurred. After the last operation, the preserved element is zero, and at least one element remains because `m < n`. Delete all remaining positive elements individually. Thus the full array is good.

For impossibility, consider any subsequence of length `L`. Before its first zero appears, the element becoming zero must survive as many operations as its initial value. Every operation removes an element, so a survivor can have experienced at most `L-1` operations. If every original value is at least `n`, it is also at least `L`, making the first zero impossible. No nonempty good subsequence exists.

Time: **O(n)**. Extra space: **O(1)**.

**3. C — Edge Addeleting** · [Statement](https://codeforces.com/contest/2277/problem/C) · `C.cpp`

Every new edge touches vertex `1`. Consequently, after removing vertex `1`, every remaining edge at every moment is an edge of the original tree.

Let `K` be the component containing `n` when vertex `1` is removed from the original tree. In any final tree, the path from `1` to `n` must begin with an edge `(1,w)` for some `w` in `K`. The rest of that path is forced: it is the original unique path from `w` to `n`. Its length is therefore

`1 + original_distance(w,n)`.

The possible starting vertices `w` are the original neighbor of `1` in `K`, or an operation endpoint belonging to `K`. An endpoint outside `K` cannot help: without vertex `1`, there are no edges connecting its original component to `K`.

Every candidate can actually be achieved. Ignore all operations except the chosen one by deleting their newly added edges. When adding `(1,w)`, delete the original edge from `1` into `K`; the resulting path has the claimed length. The original path itself remains available by ignoring every operation.

So traverse from `n` without entering `1`, recording distances. Initialize the answer to the original distance from `1` to `n`. For each endpoint reached by this traversal, maximize the answer with its recorded distance plus one. The order of operations is irrelevant because one chosen operation suffices.

Time: **O(n+m)**. Extra space: **O(n)**. The traversal is iterative.

**4. D1 — Number Operating, easy version** · [Statement](https://codeforces.com/contest/2277/problem/D1) · `D1.cpp`

First solve one target `n`. A consecutive run of `j` additions increases the value by `2^j-1`. Combining a run with the subtraction that separates it from another run gives a useful unit:

- net increase `2^j-2`;
- operation count `j+1`.

For `n >= 4`, write `P = 2^k`, where `P <= n < 2P`. The recurrence used in the program is

`f(n) = min(f(n-P+2) + k+1, 2P-n+k)`.

The first choice uses a length-`k` run and a separating subtraction, then solves the remaining increase. The second uses `k+1` additions to reach `2P-1`, then subtracts down to `n`. The starting values are `f(0)=0, f(1)=1, f(2)=3, f(3)=2`.

For example, `f(4)=6`: three additions reach `7`, and three subtractions reach `4`.

An exchange argument explains why these two choices cover an optimum. For a sequence containing `b` addition runs, let their lengths be `j_1,...,j_b`. There must be at least `b-1` subtractions. Write the number of extra subtractions as `q`. Then

`n = 1 + sum(2^j-2) - q`.

If we add `n` to the operation count, the result is

`sum(2^j + j - 1)`.

Thus minimizing operations is equivalent to selecting run lengths with total capacity `sum(2^j-2) >= n-1`, minimizing the total price `sum(2^j+j-1)`. Surplus capacity is removed by the extra subtractions. Any such selection can be realized by putting one subtraction between runs and the extra subtractions at the end.

For `n >= 2`, length-one runs have zero capacity and can be discarded. Two runs of the same length `j >= 2` can be replaced by one run of length `j+1`: capacity increases by two, while price changes by `2-j <= 0`. Repeating this replacement leaves an optimum with distinct run lengths.

All lengths below `k` together provide capacity only `2^k-2k`, which is less than `n-1`. Hence an optimum needs a run of length at least `k`. A length above `k+1` costs more than a single length-`k+1` run that already covers the target. Therefore an optimum's longest run is `k` or `k+1`.

In the latter case, that run alone is sufficient. In the former, remove one length-`k` run and solve the residual covering problem, giving the first recurrence term. This proves the recurrence.

Evaluate it for every integer in `[l,r]`. The recursive argument becomes at most `P+1` and falls below `P` after at most one more step, so evaluation takes **O(log V)** time. Total time is **O((r-l+1) log V)** per test case, with **O(log V)** stack space.

**5. D2 — Number Operating, hard version** · [Statement](https://codeforces.com/contest/2277/problem/D2) · `D2.cpp`

Enumerating the interval is now impossible. Define `G(N) = sum(f(x), x=0..N)`. The answer is `G(r)-G(l-1)`.

Within a block `[P,2P-1]`, D1 compares a recursively shifted function with a descending straight line. We can identify exactly where they cross. Set `m=n-P+2`. The recursive choice wins precisely when

`f(m)+m <= P+1`.

The left side is nondecreasing: an optimal way to reach `m+1`, followed by a subtraction, proves `f(m) <= f(m+1)+1`. Therefore binary search finds the last valid `m`, called `position[k]`. Since `f(m) >= 2` for `m >= 2`, this position is at most `P-1`.

Let `cutoff[k] = P + position[k] - 2`. On `[P,cutoff[k]]`, use the recursive expression; after that, use the straight line. These intervals include ties in the first part.

To evaluate `G(N)`, let `b=min(N,cutoff[k])` and `c=b-P+1`. Then

`G(N) = G(P-1) + G(b-P+2) - G(1) + c(k+1) + tail`.

The tail covers `b+1,...,N`. Its values decrease by one, so

`tail = (N-b) * ((2P+k-b-1) + (2P+k-N)) / 2`.

Division by two is implemented with the modular inverse of two. Each formula makes only one recursive call to a smaller highest-bit block. Precompute `G(P-1)` in increasing order of `k`; all dependencies then already exist. Small prefixes are `G(0)=0, G(1)=1, G(2)=4, G(3)=6`, and negative prefixes return zero.

Precomputation takes **O(log^3 V)**: O(log V) blocks, each with a binary search whose predicate evaluates D1. Every query takes **O(log V)** time, with **O(log V)** total auxiliary space. All arithmetic fits signed 64-bit integers because products of large counts are reduced modulo the modulus before multiplication.

**6. E — Tree Guessing** · [Statement](https://codeforces.com/contest/2277/problem/E) · `E.cpp`

Use two phases of `n-1` queries. Root the hidden tree at `1`. To measure a vertex `u`'s subtree, query from `1`, giving `u` label `n` and `1` label `n-1`. Subtract `n(n-1)` from the response. The result is its subtree size.

Process vertices by decreasing size; every parent precedes its children. For the next vertex `u`, give it label `1`. Label known vertices `2,...,i` in breadth-first order, and label later vertices by their positions in the size order.

Later vertices contribute their own labels. Remove their sum and `u`'s contribution. If the parent has label `z`, the remaining response is

`H(z) = z(z-1) + sum(z+1,...,i)`.

Breadth-first labels make each known path's maximum the larger endpoint label. Since `H(z+1)-H(z)=z-1>0`, the parent is uniquely determined.

Exactly **2n-2 queries**, **O(n^2)** local time, **O(n)** space. The code flushes queries and exits on `-1`. Test it through the supplied simulated judge; ordinary statement input cannot drive an interactive submission.

For a concrete decoding example, take the hidden edges `(1,2), (2,3), (1,4)`. The subtree sizes are `4,2,1,1`, so one processing order is `1,2,3,4`. While attaching vertex `3`, the known vertices `1,2` receive labels `2,3`, vertex `3` receives `1`, and vertex `4` receives `4`. Querying from `3` returns `3+3+1+4=11`. Subtract its own `1` and the later vertex's `4`, leaving `6`. A parent with label `2` would give `5`; a parent with label `3` gives `6`. Thus the parent is vertex `2`.

**7. F — Token Re-Moving** · [Statement](https://codeforces.com/contest/2277/problem/F) · `F.cpp`

An operation at `u` contributes its original subtree sum unless an earlier ancestor already emptied that subtree. Activate vertices in reverse permutation order. DSU components identify the roots for which each operation contributes. Build a reconstruction tree: newly activated `u` becomes the parent of each adjacent component's reconstruction root.

Let `S` be the total tokens. When joining through original edge `(u,v)`, give the new reconstruction edge weight `S-W(u,v)`, where `W(u,v)` is the token sum on `v`'s side after cutting that edge. For any answer root `r`, its contributing operations are exactly its reconstruction ancestors. Consequently its answer is `S` plus the reconstruction path's edge weights.

Original subtree sums give each edge weight in constant time. With the original tree rooted at `1`, the weight is `sub[u]` when `v` is `u`'s parent; otherwise it is `S-sub[v]`. Process the original permutation forward to accumulate answers, because reconstruction parents appear first.

Time: **O(n alpha(n))** with DSU. Space: **O(n)**. Both tree processing and DSU search are iterative.

For example, use the path `1-2-3`, token counts `[2,3,5]`, and operation order `[2,1,3]`. Reverse activation first creates separate components at `3` and `1`, then activates `2` and joins both. The reconstruction root is `2`. The edge to reconstruction child `1` has weight `8`, because cutting `(2,1)` leaves tokens `3+5` on `2`'s side. The edge to child `3` has weight `5`, because the other side contains tokens `2+3`. Starting from total `10`, the answers for roots `1,2,3` are therefore `18,10,15`. Direct simulation agrees: for root `1`, the operation at `2` costs `8` and the operation at `1` then costs `10`.

The [official editorial](https://codeforces.me/blog/entry/158113) was consulted to cross-check the D recurrence and the E/F approaches. The implementations, tests, and expanded D exchange argument were prepared for this solution set. See `VALIDATION.md` for the checks performed.
