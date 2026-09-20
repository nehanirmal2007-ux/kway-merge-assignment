# Comparison Table: Min-Heap K-Way Merge vs Pairwise Merging

| Criterion                          | Min-Heap K-Way Merge                         | Pairwise Merging                                  |
|--------------------------------------|-------------------------------------------------|------------------------------------------------------|
| Data structure used                | Min Heap (array-based binary heap), size k      | Plain arrays, merged two at a time                    |
| Heap size / working set             | O(k) — one element per list at any time         | Not applicable — no heap, but intermediate arrays grow up to size n |
| Number of passes over the data     | 1 combined pass (n extract/insert cycles)       | (k − 1) passes, one per additional list merged        |
| Comparisons (measured, this input) | 21                                                | 18                                                     |
| Copy / swap operations (measured)  | 9 heap swaps                                     | 20 array copies                                        |
| Time complexity                    | O(n log k)                                       | O(n·k)                                                 |
| Space complexity                   | O(k) extra + O(n) output                         | O(n) extra (intermediate lists) + O(n) output          |
| Scalability with more lists (k↑)   | Grows very slowly (logarithmic in k)             | Grows linearly in k — noticeably slower for many lists |
| Scalability with more data (n↑)    | Grows linearly in n                              | Grows linearly in n (but with a larger constant, k)    |
| Implementation complexity          | Slightly higher (heap insert/extract logic)      | Simple (reuses standard two-way merge)                 |
| Best suited for                    | Merging many sorted files/streams (e.g., external sort, log/transaction merging with many sources) | Merging a small, fixed number of lists (e.g., k = 2 or 3) |

**Key observation from the executed programs:** with only k = 3 small
lists, the raw operation counts are close (21 vs 18 comparisons) and
pairwise merging is not obviously worse — the constant factors and
small input size hide the asymptotic difference. The heap-based
approach's advantage only becomes decisive once k (the number of
sorted sources) grows large, which is exactly the situation it is
designed for (e.g., a financial system consolidating transactions
from dozens or hundreds of branch offices/log files simultaneously).
