# Q9 — K-Way Merge of Sorted Transaction Lists (Min Heap vs Pairwise Merging)

## Problem
A financial system receives three already-sorted transaction lists:
```
L1 = 10, 30, 50, 70
L2 = 20, 40, 60, 80
L3 = 15, 35, 55, 75
```

This repository implements and compares two approaches to merge them
into a single sorted list:

- **(a)** K-way merge using a **Min Heap**
- **(b)** Simple **pairwise merging** (merge two lists at a time)

## Repository structure
```
.
├── source/
│   ├── kway_merge_heap.c     # (a) Min-heap k-way merge, C implementation
│   └── pairwise_merge.c      # (b) Pairwise merging, C implementation
├── input/
│   └── input.txt             # the three input lists
├── output/
│   ├── kway_merge_heap       # compiled binary (a)
│   ├── pairwise_merge        # compiled binary (b)
│   ├── output_heap.txt       # captured run output of (a)
│   └── output_pairwise.txt   # captured run output of (b)
├── docs/
│   ├── trace_table.md        # step-by-step trace tables for both algorithms
│   ├── complexity_analysis.md# time/space complexity analysis
│   ├── comparison_table.md   # side-by-side comparison of both approaches
│   └── final_conclusion.md   # which approach is more suitable, and why
└── README.md
```

## How to build and run
```bash
gcc -O2 -Wall -o output/kway_merge_heap source/kway_merge_heap.c
gcc -O2 -Wall -o output/pairwise_merge  source/pairwise_merge.c

./output/kway_merge_heap
./output/pairwise_merge
```

## Result
Both programs correctly merge the input into:
```
10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80
```

## Summary of findings
| Approach              | Time Complexity | Space Complexity | Comparisons (measured) |
|------------------------|-------------------|---------------------|---------------------------|
| Min-Heap K-Way Merge   | O(n log k)         | O(k) + O(n)          | 21                          |
| Pairwise Merging       | O(n·k)             | O(n)                 | 18                          |

See `docs/final_conclusion.md` for the full justification. In short:
for this small instance (k = 3) both approaches perform similarly,
but the **min-heap approach scales far better as the number of sorted
lists (k) grows**, making it the more suitable choice for a real
financial system merging many transaction sources.
