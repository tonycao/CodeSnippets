#! /usr/bin/python

def qsort(a):
    if len(a) <= 1:
        return a
    pivot = a[len(a) / 2]
    left = [x for x in a if x < pivot]
    middle = [x for x in a if x == pivot]
    right = [x for x in a[1:] if x > pivot]
    return qsort(left) + middle + qsort(right)

print qsort([1, 3, 2, 9, 10, 7, 6, 8])