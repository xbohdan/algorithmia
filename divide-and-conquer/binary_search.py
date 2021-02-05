import sys


def binary_search(array, value):
    left = 0
    right = len(array) - 1
    while left <= right:
        middle = (left + right) // 2

        if array[middle] == value:
            return value
        if array[middle] > value:
            right = middle - 1
        else:
            left = middle + 1
    return -1


def linear_search(array, value):
    for i in range(len(array)):
        if array[i] == value:
            return i
    return -1


if __name__ == '__main__':
    data = list(map(int, input().split()))
    n = data[0]
    m = data[n + 1]
    array = data[1: n + 1]
    for value in data[n + 2:]:
        print(binary_search(array, value), end=' ')
