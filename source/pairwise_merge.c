/* =====================================================================
   pairwise_merge.c
   ----------------------------------------------------------------------
   Q9(b): Simple PAIRWISE MERGING approach for the same three lists.

   Strategy: merge L1 & L2 first (standard two-way merge of sorted
   arrays) to get an intermediate list M1, then merge M1 & L3 to get
   the final sorted output. This mirrors the "merge pass" idea used
   in classical external/merge sort when no heap is used.

   The program prints:
     - the intermediate merged list M1 (L1 + L2)
     - the final merged list (M1 + L3)
     - the number of comparisons and copy/move operations performed
   ===================================================================== */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 100

long comparisons = 0;
long copyOps = 0;

/* standard two-way merge of two sorted arrays a[0..n1-1], b[0..n2-1] */
int twoWayMerge(int a[], int n1, int b[], int n2, int out[]) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        comparisons++;
        if (a[i] <= b[j]) {
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
        copyOps++;
    }
    while (i < n1) { out[k++] = a[i++]; copyOps++; }
    while (j < n2) { out[k++] = b[j++]; copyOps++; }

    return k; /* length of merged output */
}

void printArray(const char *label, int arr[], int n) {
    printf("%-28s : [", label);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i != n - 1) printf(", ");
    }
    printf("]\n");
}

int main(void) {
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    int n1 = sizeof(L1) / sizeof(L1[0]);
    int n2 = sizeof(L2) / sizeof(L2[0]);
    int n3 = sizeof(L3) / sizeof(L3[0]);

    int M1[MAXN];   /* result of merging L1 and L2 */
    int FINAL[MAXN];/* result of merging M1 and L3 */

    printf("================  PAIRWISE MERGING APPROACH  ================\n\n");
    printArray("L1", L1, n1);
    printArray("L2", L2, n2);
    printArray("L3", L3, n3);

    printf("\n---- Pass 1: merge L1 and L2 -> M1 ----\n");
    long cmpBefore = comparisons, copyBefore = copyOps;
    int m1Len = twoWayMerge(L1, n1, L2, n2, M1);
    printArray("M1 = merge(L1,L2)", M1, m1Len);
    printf("  Comparisons in pass 1 : %ld\n", comparisons - cmpBefore);
    printf("  Copy operations pass 1: %ld\n", copyOps - copyBefore);

    printf("\n---- Pass 2: merge M1 and L3 -> FINAL ----\n");
    cmpBefore = comparisons; copyBefore = copyOps;
    int finalLen = twoWayMerge(M1, m1Len, L3, n3, FINAL);
    printArray("FINAL = merge(M1,L3)", FINAL, finalLen);
    printf("  Comparisons in pass 2 : %ld\n", comparisons - cmpBefore);
    printf("  Copy operations pass 2: %ld\n", copyOps - copyBefore);

    printf("\n================  RESULT  ================\n");
    printArray("Merged sorted output", FINAL, finalLen);

    printf("\n================  STATISTICS  ================\n");
    printf("Total elements merged       : %d\n", finalLen);
    printf("Total comparisons (all passes): %ld\n", comparisons);
    printf("Total copy operations         : %ld\n", copyOps);
    printf("Number of merge passes        : 2 (since 3 lists)\n");

    return 0;
}
