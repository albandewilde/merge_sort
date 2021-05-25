#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

// Slice represent a pointer to an array and his length
struct slice {
    int *arr;
    int length;
};

// Merge slice as in merge sort algorithm
// a and b are slices to merge
// n is the slice that is used to store sorted elements
void merge(struct slice a, struct slice b, struct slice n){
    if (a.length == 0) {
        memcpy(n.arr, b.arr, sizeof(int)*a.length);
        return;
    }
    if (b.length == 0) {
        memcpy(n.arr, a.arr, sizeof(int)*a.length);
        return;
    }

    if (a.arr[0] <= b.arr[0]) {
        n.arr[0] = a.arr[0];
        merge(
            (struct slice){
                .arr = a.arr + 1,
                .length = a.length - 1,
            },
            b,
            (struct slice){
                .arr = n.arr + 1,
                .length = n.length - 1,
            }
        );
    } else {
        int x = b.arr[0];
        memcpy(a.arr+1, a.arr, sizeof(int)*a.length);
        a.arr = a.arr+1;
        n.arr[0] = x;

        merge(
            a,
            (struct slice){
                .arr = b.arr + 1,
                .length = b.length - 1,
            },
            (struct slice){
                .arr = n.arr + 1,
                .length = n.length + 1,
            }
        );
    }
}

// MergeSort is the recursive fonction used to sort
// s is the slice to sort
// n is the slice to store sorted elements
void mergeSort(struct slice s, struct slice n){
    if (s.length <= 1) {
        memcpy(n.arr, s.arr, sizeof(int)*s.length);
        return;
    }

    int middle = s.length / 2;

    // Split s in two slice
    struct slice s0 = {
        .arr = s.arr,
        .length = middle,
    };
    struct slice s1 = {
        .arr = s.arr + middle,
        .length = s.length - middle,
    };

    // Split n in two slice
    struct slice n0 = {
        .arr = n.arr,
        .length = middle,
    };
    struct slice n1 = {
        .arr = n.arr + middle,
        .length = s.length - middle,
    };

    mergeSort(s0, n0);
    mergeSort(s1, n1);

    merge(n0, n1, n);
}

// Sort a slice using merge sort algorithm
struct slice sort(struct slice s) {
	// Empty slice to fill with sorted elements
    struct slice sorted = {
        .arr = malloc(sizeof(int)*s.length),
        .length = s.length,
    };

    mergeSort(s, sorted);

    return sorted;
}

// IsSorted return true is a []int is sorted, false otherwise
bool isSorted(struct slice s) {
    for (int i = 1; i < s.length; i++) {
        if (s.arr[i-1] > s.arr[i]) {
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
    struct slice s0 = sort((struct slice){.arr = (int[]){}, .length = 0});
    assert(isSorted(s0) == true);
    free(s0.arr);
    // Sort one element in slice
    struct slice s1 = sort((struct slice){.arr = (int[]){4}, .length = 1});
    assert(isSorted(s1) == true);
    free(s1.arr);
    // Sort odd number of elements
    struct slice s2 = sort((struct slice){.arr = (int[]){3, 8, 2, 5, 6}, .length = 5});
    assert(isSorted(s2) == true);
    free(s2.arr);
    // Sort even number of elements
    struct slice s3 = sort((struct slice){.arr = (int[]){3, 1, 5, 7, 0, 2}, .length = 6});
    assert(isSorted(s3) == true);
    free(s3.arr);


    // Generate 1000 numbers
    int *ns = generateRandomNumbers();

    int REPEAT = 7000;
    printf("Sort array of 1000 elements %d times.\n", REPEAT);

    // Total time for each sort
    long int totTime = 0;

    // Do sort REPEAT times
    for (int i = 0; i < REPEAT; i++) {
        struct slice unsorted = (struct slice){.arr = ns, .length = 1000};

        clock_t begin = clock();
        struct slice s = sort(unsorted);
        clock_t end = clock();

        totTime = totTime + (end - begin);

        // Free the memory
        free(s.arr);
    }

    // Free the unsorted list
    free(ns);

    // Display average time to sort the slice
    printf("Average time to sort the slice: %f seconds\n", (float)totTime/CLOCKS_PER_SEC/REPEAT);
}
