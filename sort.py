import timeit
import tracemalloc
import unittest
import sys
import random

sys.setrecursionlimit(3000)


def merge(lst0, lst1):
    """Merge two sorted list to an other sorted list"""
    if len(lst0) == 0:
        return lst1
    if len(lst1) == 0:
        return lst0

    if lst0[0] <= lst1[0]:
        return [lst0[0]] + merge(lst0[1:], lst1)
    return [lst1[0]] + merge(lst0, lst1[1:])


def sort(lst):
    """Sort function using merge sort algorithm"""
    if len(lst) <= 1:
        return lst
    return merge(
        sort(lst[:len(lst)//2]),
        sort(lst[len(lst)//2:]),
    )


def is_sorted(lst):
    """Check if a list is sorted"""
    for idx in range(1, len(lst)):
        if lst[idx-1] > lst[idx]:
            return False
    return True


def random_numbers():
    """Generate a list of 1000 random numbers"""
    return [random.randrange(0, 10000) for _ in range(1000)]


class TestMergeSort(unittest.TestCase):
    """Check if the algorithm is working"""
    def test_empty_list(self):
        self.assertTrue(is_sorted(sort([])))

    def test_one_element_list(self):
        self.assertTrue(is_sorted(sort([4])))

    def test_odd_number_of_elements(self):
        self.assertTrue(is_sorted(sort([3, 8, 2, 5, 6])))

    def test_even_number_of_elements(self):
        self.assertTrue(is_sorted(sort([3, 1, 5, 7, 0, 2])))


if __name__ in "__main__":
    # Generate our 1000 random numbers
    numbers = random_numbers()

    REPEAT = 7000
    print(f"Sort list of {len(numbers)} elements {REPEAT} times.")

    # List of statistics
    stats = []

    # Do sort REPEAT times
    for _ in range(REPEAT):
        tracemalloc.start()
        sort(numbers)
        snapshot = tracemalloc.take_snapshot()

        # Add statistics
        for stat in snapshot.statistics("filename"):
            # Only use statistic in this file
            for frame in stat.traceback._frames:
                if frame[0] == "sort.py":
                    stats.append(stat)

    # Make an average of stats
    count = size = 0
    for stat in stats:
        count += stat.count
        size += stat.size
    count = round(count/REPEAT)
    size = round(size/REPEAT)

    print("Average memory used:")
    print(
        f"Size of memory blocks={size} B, " +
        f"Number of memory blocks={count}, " +
        f"average={round(size/count)} B"
    )

    time = timeit.timeit(lambda: sort(numbers), "gc.enable()", number=REPEAT)
    print(f"Average of time spend to sort: {time/REPEAT}s")
