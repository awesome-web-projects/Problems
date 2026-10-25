**Codeforces 2277 solution set**

Seven independent C++20 submissions are included:

| File | Problem | Time complexity |
|---|---|---|
| `A.cpp` | Subset Selecting | O(n) |
| `B.cpp` | Sequence Decreasing | O(n) |
| `C.cpp` | Edge Addeleting | O(n+m) |
| `D1.cpp` | Number Operating, easy | O((r-l+1) log V) |
| `D2.cpp` | Number Operating, hard | O(log V) per query; O(log^3 V) initialization |
| `E.cpp` | Tree Guessing, interactive | O(n^2); exactly 2n-2 queries |
| `F.cpp` | Token Re-Moving | O(n alpha(n)) |

**Individual complete write-ups**

Each document includes the problem summary, complete reasoning and correctness argument, complexity, worked examples, and the full C++20 source:

- [A — Subset Selecting](A.md)
- [B — Sequence Decreasing](B.md)
- [C — Edge Addeleting](C.md)
- [D1 — Number Operating, easy version](D1.md)
- [D2 — Number Operating, hard version](D2.md)
- [E — Tree Guessing, interactive](E.md)
- [F — Token Re-Moving](F.md)

`EXPLANATIONS.md` contains the algorithms and correctness arguments. `VALIDATION.md` records the completed checks. `test_solutions.py` contains independent brute-force references and a local interactive judge for E.

Build one submission with GCC:

```sh
g++ -std=c++20 -O2 -Wall -Wextra A.cpp -o A
```

Or, in a Visual Studio developer terminal:

```bat
cl /std:c++20 /EHsc /O2 /W4 A.cpp
```

Build all seven programs under their corresponding names, then run the checks:

```sh
python test_solutions.py --bin-dir . --stress
```

The checker accepts executable names with or without `.exe`. Python needs only its standard library. Its fixed random seed is `2277`.

For E, submit `E.cpp` to the original interactive judge. Its input/output is a query protocol, so feeding it a list of tree edges as ordinary input will not work. The included checker supplies the protocol and verifies the reconstructed tree and query limit.
