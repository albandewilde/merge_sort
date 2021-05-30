package main

import (
	"math/rand"
	"testing"
)

var numbers []int

func init() {
	numbers = generateRandomNumbers()
}

//// Merge sort using copy implementation

// MergeCopy slice as in merge sort algorithm
// a and b are slices to merge
// n is the slice that is used to store sorted elements
func mergeCopy(a, b, n []int) {
	if len(a) == 0 || len(b) == 0 {
		return
	}

	if a[0] <= b[0] {
		n[0] = a[0]
		mergeCopy(a[1:], b, n[1:])
	} else {
		x := b[0]
		copy(a[1:len(a)+1], a)
		a = a[1 : len(a)+1]
		n[0] = x

		mergeCopy(a, b[1:], n[1:])
	}
}

// MergeSortCopy is the recursive fonction used to sort
// s is the slice to sort
// n is the slice to store sorted elements
func mergeSortCopy(s, n []int) {
	if len(s) <= 1 {
		copy(n, s)
		return
	}

	middle := len(s) / 2
	mergeSortCopy(s[:middle], n[:middle])
	mergeSortCopy(s[middle:], n[middle:])
	mergeCopy(
		n[:middle],
		n[middle:],
		n,
	)
}

// SortCopy, sort a slice using merge sort algorithm
// with only ont underlaying array and manipulate data in it
func SortCopy(s []int) []int {
	// Empty slice to fill with sorted elements
	sorted := make([]int, len(s))
	mergeSortCopy(s, sorted)
	return sorted
}

//// Merge sort using ping pong implementation

// MergePingPong slice as in merge sort algorithm
// src[offset:pivot] and src[pivot:offsetMax] are the slice to merge into dst[offset:offsetMax]
func mergePingPong(src, dst []int, offset, pivot, offsetMax int) {
	if offsetMax < pivot {
		_ = append(dst[offset:offset], src[offset:offsetMax]...)
		return
	}

	offsetA, offsetMaxA := offset, pivot
	offsetB, offsetMaxB := pivot, offsetMax

	for offsetA < offsetMaxA && offsetB < offsetMaxB {
		valA, valB := src[offsetA], src[offsetB]
		if valA < valB {
			dst[offset] = valA
			offsetA++
		} else {
			dst[offset] = valB
			offsetB++
		}
		offset++
	}
	if offsetA < offsetMaxA {
		_ = append(dst[offset:offset], src[offsetA:offsetMaxA]...)
	}
	if offsetB < offsetMaxB {
		_ = append(dst[offset:offset], src[offsetB:offsetMaxB]...)
	}
}

// MergeSortPingPong is the recursive fonction used to sort
func mergeSortPingPong(in, out []int) {
	length := len(in)

	for pivotLength := 1; pivotLength <= pivotMax(length); pivotLength *= 2 {
		var offset int
		for offset < length {
			pivot := offset + pivotLength
			offsetMax := min(length, offset+2*pivotLength)
			mergePingPong(in, out, offset, pivot, offsetMax)
			offset = offsetMax
		}
		in, out = out, in
	}
	in = out
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// PivotMax get the maximum pivot
func pivotMax(length int) int {
	return (length / 2) + (length % 2)
}

// SortPingPong, sort a slice using merge sort algorithm
// with two underlaying array and switching the in and out
func SortPingPong(s []int) []int {
	// Copy the slice to preserve original slice
	src := make([]int, 0, len(s))
	copy(src, s)

	// Empty slice to fill with sorted elements
	dst := make([]int, len(s))

	mergeSortPingPong(src, dst)

	return dst
}

///

// IsSorted return true if a []int is sorted, false otherwise
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

var cases = [][]int{
	{},
	{4},
	{3, 8, 2, 5, 6},
	{3, 1, 5, 7, 0, 2},
}

func TestSortCopy(t *testing.T) {
	for _, test := range cases {
		if !isSorted(SortCopy(test)) {
			t.Errorf("The slice (%v) is not sorted", test)
		}
	}
}

func TestSortPingPong(t *testing.T) {
	for _, test := range cases {
		if !isSorted(SortPingPong(test)) {
			t.Errorf("The slice (%v) is not sorted", test)
		}
	}
}

func BenchmarkMergeSortCopy(b *testing.B) {
	for i := 0; i < b.N; i++ {
		SortCopy(numbers)
	}
}

func BenchmarkMergeSortPingPing(b *testing.B) {
	for i := 0; i < b.N; i++ {
		SortPingPong(numbers)
	}
}
