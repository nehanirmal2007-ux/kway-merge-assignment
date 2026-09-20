# Final Conclusion

Both approaches correctly merge the three sorted transaction lists
(L1, L2, L3) into the single sorted sequence:

**10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80**

## Which approach is more suitable?

- For **k = 3 small lists** (this assignment's exact input), the two
  approaches perform very similarly. Pairwise merging is simple to
  implement and, at this tiny scale, even used fewer raw comparisons
  (18 vs 21) than the heap-based method in the measured run, because
  the constant overhead of maintaining a heap is not yet "paid off"
  by savings in comparisons.

- However, the **asymptotic (big-O) analysis** tells the real story:
  - Min-heap k-way merge: **O(n log k)**
  - Pairwise merging: **O(n·k)**

  As the number of sorted sources **k** grows (which is the realistic
  scenario for a financial system that may need to merge transaction
  logs from many branches, ATMs, or payment gateways simultaneously),
  pairwise merging's cost grows **linearly with k**, while the
  heap-based approach's cost grows only **logarithmically with k**.
  For example, merging 100 sorted files of total size n: pairwise
  merging does roughly 100× more comparison work per element than
  when k = 2, whereas the heap approach only pays an extra log₂(100)
  ≈ 6.6× factor.

- The heap approach also keeps a **bounded working set of size k**
  in memory (just one candidate element per source list) instead of
  materializing progressively larger intermediate merged lists, which
  matters when lists are read as streams (e.g., from disk/files) and
  cannot all be held in memory at once.

## Recommendation

**The Min-Heap K-Way Merge is the more suitable and scalable approach**
for a financial system merging sorted transaction lists, especially as
the number of input sources increases. Pairwise merging remains an
acceptable, simpler alternative only when the number of lists to merge
(k) is small and fixed (such as the k = 3 case demonstrated here), but
it does not scale well and should be avoided for systems that need to
merge many transaction sources concurrently.
