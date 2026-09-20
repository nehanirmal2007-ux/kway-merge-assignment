# Complexity Analysis

Let:
- `k` = number of sorted lists (here k = 3)
- `n` = total number of elements across all lists (here n = 12)
- each list assumed roughly `n/k` elements

## 1. K-Way Merge Using a Min Heap

**Algorithm:** Build a heap of size k from the first element of each list.
Repeat n times: extract-min (O(log k)), output it, insert the next
element from the same source list (O(log k)).

| Operation                       | Cost            |
|----------------------------------|------------------|
| Build initial heap (k inserts)   | O(k log k)       |
| n extract-min + insert cycles    | O(n log k)       |
| **Total time complexity**        | **O(n log k)**   |
| **Space complexity**             | **O(k)** extra (heap) + **O(n)** for output array |

Because k is usually much smaller than n (k = number of files/lists,
n = total records), O(n log k) scales very well as n grows, and the
log k factor grows extremely slowly even if k increases.

## 2. Pairwise (Sequential) Merging

**Algorithm:** Merge list 1 and list 2 into an intermediate list M1
(cost proportional to |L1| + |L2|). Merge M1 with list 3 (cost
proportional to |M1| + |L3|), and so on for all k lists.

For k lists, the intermediate result grows with every pass:
- Pass 1 touches ~2·(n/k) elements
- Pass 2 touches ~(2n/k + n/k) = 3·(n/k) elements
- Pass i touches ~(i+1)·(n/k) elements
- ...
- Pass (k-1) touches ~k·(n/k) = n elements

Summing all passes gives a quadratic-in-k growth:

Total comparisons ≈ (n/k) · (2 + 3 + 4 + ... + k) = O(n·k)

| Operation                        | Cost           |
|------------------------------------|------------------|
| k − 1 merge passes                | O(n·k) total (worst case) |
| **Total time complexity**         | **O(n·k)**       |
| **Space complexity**              | **O(n)** extra (intermediate arrays), plus O(n) output |

For our specific instance (k = 3 lists, n = 12) the difference between
`O(n log k)` and `O(n·k)` is not very visible because k is tiny
(log₂3 ≈ 1.58 vs k = 3), but the growth trend is already there and
becomes dramatic as k increases (e.g., merging 100 sorted files).

## 3. Measured Operation Counts (from program execution)

| Metric                         | Min-Heap K-Way Merge | Pairwise Merging |
|----------------------------------|------------------------|---------------------|
| Comparisons                     | 21                      | 18                  |
| Swap / copy operations          | 9 (heap swaps)          | 20 (array copies)   |
| Auxiliary space used            | O(k) = O(3)             | O(n) = O(12)        |
| Number of "passes" over data    | 1 unified pass          | 2 sequential passes |

For this small instance (only 3 lists of 4 elements), the constant
factors dominate and the pairwise approach even shows slightly fewer
raw comparisons than the heap approach - this is expected, since
asymptotic complexity only predicts behaviour as `n` and `k` grow
large, not for tiny fixed inputs. Section `comparison_table.md`
and `final_conclusion.md` discuss why the heap-based approach is
still the theoretically and practically superior choice as the
problem scales up.
