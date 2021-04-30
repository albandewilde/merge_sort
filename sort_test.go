package main

import (
	"math/rand"
	"testing"
)

var numbers []int

func init() {
	numbers = generateRandomNumbers()
}

// Merge slice as in merge sort algorithm
// a and b are slices to merge
// n is the slice that is used to store sorted elements
func merge(a, b, n []int) {
	if len(a) == 0 {
		copy(n, b)
		return
	}
	if len(b) == 0 {
		copy(n, a)
		return
	}

	if a[0] <= b[0] {
		n[0] = a[0]
		merge(a[1:], b, n[1:])
	} else {
		x := b[0]
		copy(a[1:len(a)+1], a)
		a = a[1 : len(a)+1]
		n[0] = x

		merge(a, b[1:], n[1:])
	}
}

// MergiSort is the recursive fonction used to sort
// s is the slice to sort
// n is the slice to store sorted elements
func mergeSort(s []int, n []int) {
	if len(s) <= 1 {
		copy(n, s)
		return
	}

	middle := len(s) / 2
	mergeSort(s[:middle], n[:middle])
	mergeSort(s[middle:], n[middle:])
	merge(
		n[:middle],
		n[middle:],
		n,
	)
}

// Sort a slice using merge sort algorithm
func Sort(s []int) []int {
	if len(s) <= 1 {
		return s
	}

	// Empty slice to fill with sorted elements
	sorted := make([]int, len(s))
	mergeSort(s, sorted)
	return sorted
}

// IsSorted return true is a []int is sorted, false otherwise
func isSorted(s []int) bool {
	for i := 1; i < len(s); i++ {
		if s[i-1] > s[i] {
			return false
		}
	}
	return true
}

// GenerateRandomNumbers generate a slice of 1000 random numbers
func generateRandomNumbers() []int {
	numbers := make([]int, 1000)

	for i := 0; i < 1000; i++ {
		numbers[i] = rand.Intn(10000)
	}

	return numbers
}

func TestSortEmptySlice(t *testing.T) {
	if !isSorted(Sort([]int{})) {
		t.Errorf("The slice is not sorted")
	}
}

func TestSortOneElementInSlice(t *testing.T) {
	if !isSorted(Sort([]int{4})) {
		t.Errorf("The slice is not sorted")
	}
}

func TestSortOddNumberOfElements(t *testing.T) {
	if !isSorted(Sort([]int{3, 8, 2, 5, 6})) {
		t.Errorf("The slice is not sorted")
	}
}

func TestSortEvenNumberOfElements(t *testing.T) {
	if !isSorted(Sort([]int{3, 1, 5, 7, 0, 2})) {
		t.Errorf("The slice is not sorted")
	}
}

func BenchmarkMergeSort(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Sort(numbers)
	}
}
