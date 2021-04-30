package main

import (
	"encoding/json"
	"log"
	"os"
	"testing"
)

// Merge slice as in merge sort algorithm
func merge(a, b []int) []int {
	if len(a) == 0 {
		return b
	}
	if len(b) == 0 {
		return a
	}

	if a[0] <= b[0] {
		return append([]int{a[0]}, merge(a[1:], b)...)
	}
	return append([]int{b[0]}, merge(a, b[1:])...)
}

// Sort a slice using merge sort algorithm
func sort(s []int) []int {
	if len(s) <= 1 {
		return s
	}
	return merge(
		sort(s[:len(s)/2]),
		sort(s[len(s)/2:]),
	)
}

// ReadNumbers form the `./list.json` file
func readNumbers() []int {
	list, err := os.ReadFile("./list.json")
	if err != nil {
		log.Fatal(err)
	}
	var numbers []int
	err = json.Unmarshal(list, &numbers)
	if err != nil {
		log.Fatal(err)
	}

	return numbers
}

func TestMergeSort(t *testing.T) {
	numbers := readNumbers()
	numbers = sort(numbers)

	for i := 1; i < len(numbers); i++ {
		if numbers[i-1] > numbers[i] {
			t.Errorf("The list isn't sorted")
			return
		}
	}
}

func BenchmarkMergeSort(b *testing.B) {
	numbers := readNumbers()

	b.Run("sort", func(b *testing.B) { sort(numbers) })
}
