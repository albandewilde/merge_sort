#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// Merge arrays as in merge sort algorithm
// Dst is the array that is used to store sorted elements
// src0 and src1 are array to merge
void merge(int *dst, int dstLen, int* src0, int src0Len, int *src1, int src1Len) {
    if (src0Len == 0 || src1Len == 0) {
        return;
    }

    if (src0[0] <= src1[0]) {
        dst[0] = src0[0];
        merge(
            dst + 1, dstLen - 1,
            src0 + 1, src0Len - 1,
            src1, src1Len
        );
    } else {
        int x = src1[0];
        memcpy(src0+1, src0, sizeof(int)*src0Len);
        src0 = src0 + 1;
        dst[0] = x;

        merge(
            dst + 1, dstLen - 1,
            src0, src0Len,
            src1 + 1, src1Len - 1
        );
    }
}

// MergeSort is the recursive function used to sort
// toSort is the array to sort
// sorted is the array to store sorted elements
void mergeSort(int *toSort, int toSortLen, int *sorted, int sortedLen){
    if (toSortLen <= 1) {
        memcpy(sorted, toSort, sizeof(int)*toSortLen);
        return;
    }

    int middle = toSortLen / 2;

    mergeSort(toSort, middle, sorted, middle);
    mergeSort(toSort + middle, toSortLen - middle, sorted + middle, toSortLen - 1);

    merge(
        sorted, sortedLen,
        sorted, middle,
        sorted + middle, toSortLen - middle
    );
}

// Sort an array using merge sort algorithm
void sort(int *s, int sLen, int **sorted, int *sortedLen) {
    *sorted = malloc(sizeof(int)*sLen);
    *sortedLen= sLen;

    mergeSort(s, sLen, *sorted, sLen);
}

// IsSorted return true is a []int is sorted, false otherwise
bool isSorted(int *s, int len) {
    for (int i = 1; i < len; i++) {
        if (s[i-1] > s[i]) {
            return false;
        }
    }
    return true;
}

// Generate an array of 1000 random numbers
int *generateRandomNumbers() {
    int *n = malloc(sizeof(int)*1000);

    for (int i = 0; i < 1000; i++) {
        n[i] = random() % 10000;
    }

    return n;
}

void main() {
    // Sort empty slice
    int *s0;
    int l0;
    sort((int[]){}, 0, &s0, &l0);
    assert(l0 == 0);
    assert(isSorted(s0, l0) == true);
    free(s0);
    // Sort one element in slice
    int *s1;
    int l1;
    sort((int[]){4}, 1, &s1, &l1);
    assert(l1 == 1);
    assert(isSorted(s1, l1) == true);
    free(s1);
    // Sort odd number of elements
    int *s2;
    int l2;
    sort((int[]){3, 8, 2, 5, 6}, 5, &s2, &l2);
    assert(l2 == 5);
    assert(isSorted(s2, l2) == true);
    free(s2);
    // Sort even number of elements
    int *s3;
    int l3;
    sort((int[]){3, 1, 5, 7, 0, 2}, 6, &s3, &l3);
    assert(isSorted(s3, l3) == true);
    free(s3);


    // Generate 1000 numbers
    int *unsorted = generateRandomNumbers();

    int REPEAT = 7000;
    printf("Sort array of 1000 elements %d times.\n", REPEAT);

    // Total time for each sort
    long int totTime = 0;

    int *sorted;
    int len = 0;
    // Do sort REPEAT times
    for (int i = 0; i < REPEAT; i++) {
        clock_t begin = clock();
        sort(unsorted, 1000, &sorted, &len);
        clock_t end = clock();

        totTime = totTime + (end - begin);

        // Free the memory
        free(sorted);
    }

    // Free the unsorted list
    free(unsorted);

    // Display average time to sort the slice
    printf("Average time to sort the slice: %f seconds\n", (float)totTime/CLOCKS_PER_SEC/REPEAT);
}
