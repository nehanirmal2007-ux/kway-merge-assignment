/* =====================================================================
   kway_merge_heap.c
   ----------------------------------------------------------------------
   Q9(a): Represent three already-sorted lists using arrays and merge
   them using a K-WAY MERGE based on a MIN HEAP.

   The heap stores at most K (=3) elements at any time - one candidate
   element from each list that has not yet been fully consumed.

   The program prints:
     - the initial heap state (heap build)
     - the heap state after every extract-min + insert-next operation
     - the merged output
     - the number of comparisons and heap operations performed
   ===================================================================== */

#include <stdio.h>
#include <stdlib.h>

#define K 3          /* number of input lists                       */
#define MAXN 100      /* max elements per list                       */

/* ---- a heap node remembers which list & which position it came from */
typedef struct {
    int value;
    int listIndex;   /* 0,1,2 -> L1,L2,L3                            */
    int elemIndex;   /* index of this element inside its own list    */
} HeapNode;

HeapNode heap[K];
int heapSize = 0;

/* statistics */
long comparisons = 0;
long heapOperations = 0;   /* sift-up / sift-down swaps               */

/* ---------------------------------------------------------------- */
void printHeap(const char *label) {
    printf("%-28s : [", label);
    for (int i = 0; i < heapSize; i++) {
        printf("(v=%d,L%d)", heap[i].value, heap[i].listIndex + 1);
        if (i != heapSize - 1) printf(", ");
    }
    printf("]\n");
}

void swapNodes(HeapNode *a, HeapNode *b) {
    HeapNode t = *a; *a = *b; *b = t;
    heapOperations++;
}

/* sift the element at index i DOWN so the min-heap property holds   */
void siftDown(int i) {
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;

        if (left < heapSize) {
            comparisons++;
            if (heap[left].value < heap[smallest].value) smallest = left;
        }
        if (right < heapSize) {
            comparisons++;
            if (heap[right].value < heap[smallest].value) smallest = right;
        }
        if (smallest == i) break;
        swapNodes(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

/* sift the element at index i UP so the min-heap property holds     */
void siftUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        comparisons++;
        if (heap[i].value < heap[parent].value) {
            swapNodes(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

void heapInsert(HeapNode node) {
    heap[heapSize] = node;
    heapSize++;
    siftUp(heapSize - 1);
}

HeapNode heapExtractMin(void) {
    HeapNode top = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    if (heapSize > 0) siftDown(0);
    return top;
}

/* ---------------------------------------------------------------- */
int main(void) {
    int lists[K][MAXN];
    int lens[K];

    /* -------- the three already-sorted transaction lists -------- */
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    lens[0] = sizeof(L1) / sizeof(L1[0]);
    lens[1] = sizeof(L2) / sizeof(L2[0]);
    lens[2] = sizeof(L3) / sizeof(L3[0]);

    for (int i = 0; i < lens[0]; i++) lists[0][i] = L1[i];
    for (int i = 0; i < lens[1]; i++) lists[1][i] = L2[i];
    for (int i = 0; i < lens[2]; i++) lists[2][i] = L3[i];

    int totalN = lens[0] + lens[1] + lens[2];
    int merged[MAXN];
    int mergedCount = 0;

    printf("================  K-WAY MERGE USING MIN HEAP  ================\n\n");
    printf("Input lists:\n");
    for (int k = 0; k < K; k++) {
        printf("  L%d = ", k + 1);
        for (int i = 0; i < lens[k]; i++) printf("%d ", lists[k][i]);
        printf("\n");
    }
    printf("\n---- Building initial heap (1 element from each list) ----\n");

    /* Step 1: insert the first element of every list into the heap */
    for (int k = 0; k < K; k++) {
        HeapNode node = { lists[k][0], k, 0 };
        heapInsert(node);
        char label[40];
        sprintf(label, "Insert L%d[0]=%d", k + 1, lists[k][0]);
        printHeap(label);
    }
    printHeap("Initial heap built");

    printf("\n---- Extract-min / insert-next cycle ----\n");

    /* Step 2: repeatedly pull the min, output it, push the next
       element from the SAME list (if any remain)                  */
    int step = 1;
    while (heapSize > 0) {
        HeapNode minNode = heapExtractMin();
        merged[mergedCount++] = minNode.value;

        printf("\nStep %d: extracted min = %d (from L%d)\n",
               step, minNode.value, minNode.listIndex + 1);
        printHeap("  Heap after extraction");

        int nextIdx = minNode.elemIndex + 1;
        if (nextIdx < lens[minNode.listIndex]) {
            HeapNode nextNode = { lists[minNode.listIndex][nextIdx],
                                   minNode.listIndex, nextIdx };
            heapInsert(nextNode);
            printf("  Insert next L%d[%d]=%d\n",
                   minNode.listIndex + 1, nextIdx, nextNode.value);
            printHeap("  Heap after insertion");
        } else {
            printf("  List L%d is exhausted - nothing to insert\n",
                   minNode.listIndex + 1);
        }
        step++;
    }

    printf("\n================  RESULT  ================\n");
    printf("Merged sorted output (%d elements):\n  ", mergedCount);
    for (int i = 0; i < mergedCount; i++) {
        printf("%d", merged[i]);
        if (i != mergedCount - 1) printf(", ");
    }
    printf("\n");

    printf("\n================  STATISTICS  ================\n");
    printf("Total elements merged      : %d\n", mergedCount);
    printf("Max heap size used         : %d (== K)\n", K);
    printf("Total comparisons          : %ld\n", comparisons);
    printf("Total heap swap operations : %ld\n", heapOperations);
    printf("Total heap ops (ins+ext)   : %d\n", totalN + K);

    return 0;
}
