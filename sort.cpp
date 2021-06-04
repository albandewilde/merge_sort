#include <iostream>
#include <cstring>
#include <cassert>
#include <iterator>

// Slice represent a pointer to an array and his length
class Slice {
    public:
        int *arr;
        int len;

    private:
        void mergeSort(Slice) noexcept;
        void merge(Slice, Slice) noexcept;

    public:
        static Slice sftnew(int *, int) noexcept; // Soft new to get a Slice without copying the underlaying array

    public:
        Slice() = default;
        Slice(int *, int);
        // Delete method to free the underlaying array
        // Don't use destructor because we don't always want to remove the underlaying array
        void del() noexcept;
        Slice sort() noexcept;
        bool isSorted() noexcept;
};

Slice::Slice(int *array, int length) {
    arr = (int*)std::calloc(length, sizeof(int));
    std::copy(array, array+length, arr);

    len = length;
}

Slice Slice::sftnew(int *array, int length) noexcept {
    Slice s;
    s.arr = array;
    s.len = length;

    return s;
}

void Slice::del() noexcept {
    std::free(arr);
    len = 0;
}

// Merge Slice as in merge sort algorithm
// a and b are Slices to be merge in this
void Slice::merge(Slice a, Slice b) noexcept {
    if (a.len == 0 || b.len == 0) {
        return;
    }

    if (a.arr[0] <= b.arr[0]) {
        arr[0] = a.arr[0];

        Slice s = Slice::sftnew(a.arr + 1, a.len - 1);
        Slice::sftnew(arr + 1, len - 1).merge(s, b);
    } else {
        int x = b.arr[0];
        std::copy(a.arr, a.arr+a.len, a.arr+1);
        a.arr = a.arr + 1;
        arr[0] = x;

        Slice s = Slice::sftnew(b.arr + 1, b.len - 1);
        Slice::sftnew(arr + 1, len - 1).merge(a, s);
    }
}

// MergeSort is the recursive function user to sort
// n is the Slice to store sorted elements
void Slice::mergeSort(Slice n) noexcept {
    if (len <= 1) {
        std::copy(arr, arr+len, n.arr);
        return;
    }

    int middle = len / 2;

    // Slit the Slice in two Slice
    Slice s0 = Slice::sftnew(arr, middle);
    Slice s1 = Slice::sftnew(arr + middle, len - middle);

    // Split n in two Slice
    Slice n0 = Slice::sftnew(n.arr, middle);
    Slice n1 = Slice::sftnew(n.arr + middle, len - middle);

    s1.mergeSort(n1);

    n.merge(n0, n1);
}

// Sort a Slice using merge sort algorithm
Slice Slice::sort() noexcept {
	// Empty Slice to fill with sorted elements
    Slice sorted;
    //sorted.arr = (int*)malloc(sizeof(int)*len);
    sorted.arr = (int*)std::calloc(len, sizeof(int));
    sorted.len = len;

    mergeSort(sorted);

    return sorted;
}

bool Slice::isSorted() noexcept {
    for (int i = 1; i < len; i++) {
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Generate an array of 1000 random numbers
int *generateRandomNumbers() {
    int *n = (int*)std::calloc(1000, sizeof(int));

    for (int i = 0; i < 1000; i++) {
        n[i] = std::rand() % 10000;
    }

    return n;
}

int main() {
    // Sort empty Slice
    int a0[] = {};
    Slice s0(a0, 0);
    Slice r0 = s0.sort();
    assert(r0.isSorted() == true);
    s0.del();
    r0.del();
    // Sort one element in Slice
    int a1[] = {4};
    Slice s1(a1, 1);
    Slice r1 = s1.sort();
    assert(r1.isSorted() == true);
    s1.del();
    r1.del();
    // Sort odd number of elements
    int a2 [] = {3, 8, 2, 5, 6};
    Slice s2(a2, 5);
    Slice r2 = s2.sort();
    assert(r2.isSorted() == true);
    s2.del();
    r2.del();
    // Sort even number of elements
    int a3[] = {3, 1, 5, 7, 0, 2};
    Slice s3(a3, 6);
    Slice r3 = s3.sort();
    assert(r3.isSorted() == true);
    s3.del();
    r3.del();


    // Generate our 1k random numbers
    int *ns = generateRandomNumbers();
    Slice unordered = Slice(ns, 1000);
    free(ns);

    int REPEAT = 7000;
    std::cout << "Sort array of 1000 elements " << REPEAT << " times." << std::endl;

    // Total time for each sort
    long int totTime = 0;

    // Do sort REPEAT times
    for (int i = 0; i < REPEAT; i++) {
        clock_t begin = clock();
        Slice s = unordered.sort();
        clock_t end = clock();

        totTime = totTime + (end - begin);

        // Delete the sorted slice
        s.del();
    }

    // Delete the unordered slice
    unordered.del();

    // Display results
    std::cout << "Average time to sortt the slice: " << (float)totTime/CLOCKS_PER_SEC/REPEAT << " seconds" << std::endl;

    return 0;
}
