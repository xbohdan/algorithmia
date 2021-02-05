import sys


def get_majority_element(seq, default=None):
    """Find which element of the sequence is in the majority.

    Return the default if no such element exists.

    Use the Boyer-Moore majority vote algorithm.
    """
    candidate = default
    count = 0
    for x in seq:
        if count == 0:
            candidate = x
            count = 1
        else:
            count = count + 1 if candidate == x else count - 1

    if seq.count(candidate) > len(seq) // 2:
        return candidate
    return default


if __name__ == '__main__':
    seq = list(map(int, input().split()))
    print(get_majority_element(seq))
