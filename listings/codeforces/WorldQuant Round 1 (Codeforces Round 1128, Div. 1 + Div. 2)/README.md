# Codeforces Contest 2261 — C++17 Solutions and Explanations

This package contains all ten submission variants discussed in the chat. Each has a standalone source file named `comp_2261_<problem>.cpp` and a guide named `exp_2261_<problem>.md`.

| Problem | C++17 submission | Explanation | Main technique |
|---|---|---|---|
| A | [comp_2261_A.cpp](comp_2261_A.cpp) | [exp_2261_A.md](exp_2261_A.md) | Paired-turn invariant and minimax bounds |
| B | [comp_2261_B.cpp](comp_2261_B.cpp) | [exp_2261_B.md](exp_2261_B.md) | Minimum/maximum common binary prefix |
| C | [comp_2261_C.cpp](comp_2261_C.cpp) | [exp_2261_C.md](exp_2261_C.md) | Parity counts and losing states |
| D1 | [comp_2261_D1.cpp](comp_2261_D1.cpp) | [exp_2261_D1.md](exp_2261_D1.md) | Optimal interval construction |
| D2 | [comp_2261_D2.cpp](comp_2261_D2.cpp) | [exp_2261_D2.md](exp_2261_D2.md) | Double XOR hashing, greedy cuts, endpoint pairing |
| E | [comp_2261_E.cpp](comp_2261_E.cpp) | [exp_2261_E.md](exp_2261_E.md) | Run compression and monotonic deque |
| F1 | [comp_2261_F1.cpp](comp_2261_F1.cpp) | [exp_2261_F1.md](exp_2261_F1.md) | Three-zero grid encoding |
| F2 | [comp_2261_F2.cpp](comp_2261_F2.cpp) | [exp_2261_F2.md](exp_2261_F2.md) | Optimal three-zero grid encoding |
| G | [comp_2261_G.cpp](comp_2261_G.cpp) | [exp_2261_G.md](exp_2261_G.md) | XOR/AND characterization and offline bit counting |
| H | [comp_2261_H.cpp](comp_2261_H.cpp) | [exp_2261_H.md](exp_2261_H.md) | Bit-directed DFS and Hamming error correction |

F1 and F2 intentionally contain the same complete construction. It uses at most three zeros, satisfying both versions. Each source compiles independently.

## Building and running

Use a GNU C++17-compatible compiler, such as GNU G++17 on Codeforces:

```text
g++ -std=c++17 -O2 -pipe comp_2261_A.cpp -o solution
```

Replace the source filename for another problem. Each file has its own `main`; compile one source at a time. The sources use the GNU header `bits/stdc++.h`.

On Windows PowerShell, for a compiler producing `solution.exe`, one way to supply a saved input file is:

```powershell
Get-Content -Raw input.txt | .\solution.exe
```

Input models differ:

- A, B, C, D1, D2, E, and G start with a test-case count.
- F1 and F2 read only a single `n`, then print all encoded grids and one shared decoder table.
- H starts with `first` or `second`, followed by a test-case count. The judge connects its two runs; consult its guide for local testing.

## Performance notes

All submissions enable fast iostreams and use newlines without per-line flushing. The guides explain the problem-specific optimizations, numeric bounds, and mistakes to avoid.

G deliberately uses substantial memory to replace hash queries with direct frequency-array access. Its intended memory limit is 1 GiB; see its guide for an allocation estimate. D2 uses two 64-bit XOR hashes and has a negligible randomized collision risk.

## Verification scope

Independent Python models checked the algorithms:

| Problem | Check |
|---|---|
| A | Minimax for all nonempty ownership masks at `n=2..8`, for one through three complete turn pairs; all six samples |
| B | All 9,330 arrays of lengths `1..5` with values `0..5`, against every legal next move |
| C | All 860 odd/even-count states of sizes `1..40`, against minimax |
| D1 | Unique reports for every `n=1..1000`; endpoint-count proof supplies optimality |
| D2 | 43,866 configurations, checking both unique reports and the exact minimum count |
| E | 250,952 `(RBS,k)` combinations, plus all nine samples |
| F1/F2 | Every target at every allowed size: 21,864 targets, at most three zeros each |
| G | 1,364 exhaustive small arrays, 10,000 random arrays, and all four samples |
| H | 43,120 corruption/decoding cases, including every corrupted node for six full-size messages |

No local GNU/Clang C++ compiler was available in this workspace. The source files were reviewed, but were not compiled or submitted to Codeforces here. The algorithm checks above are distinct from binary-level or online-judge verification.

The package also checks that every expected source and explanation exists, the guides link to their source, and the ZIP reproduces the files exactly.

## References

- [Contest](https://codeforces.com/contest/2261)
- [Official tutorial, including the full F2 lower bound](https://codeforces.com/blog/entry/157917)

Individual guides link to the corresponding problem statement.
