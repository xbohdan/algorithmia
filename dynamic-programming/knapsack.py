import numpy as np
import sys


def optimal_weight(capacity, weights):
    amount = len(weights)
    result = np.zeros((amount + 1, capacity + 1), dtype=int)
    for i in range(1, amount + 1):
        w = weights[i - 1]
        for j in range(1, capacity + 1):
            result[i, j] = result[i - 1, j]
            if w <= j:
                weight = result[i - 1, j - w] + w
                if result[i, j] < weight:
                    result[i, j] = weight
    print(result)
    return result[amount, capacity]


if __name__ == '__main__':
    input = sys.stdin.read()
    W, n, *w = list(map(int, input.split()))
    print(optimal_weight(W, w))
