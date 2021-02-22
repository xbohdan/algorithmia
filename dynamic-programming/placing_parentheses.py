import sys


def evaluate(a, b, operation):
    if operation == '+':
        return a + b
    if operation == '-':
        return a - b
    if operation == '*':
        return a * b
    assert False


def extrema(i, j, minima, maxima, operations):
    minimum = sys.maxsize
    maximum = -sys.maxsize - 1
    for k in range(i, j):
        a = evaluate(minima[i][k], minima[k + 1][j], operations[k])
        b = evaluate(minima[i][k], maxima[k + 1][j], operations[k])
        c = evaluate(maxima[i][k], minima[k + 1][j], operations[k])
        d = evaluate(maxima[i][k], maxima[k + 1][j], operations[k])
        minimum = min(minimum, a, b, c, d)
        maximum = max(maximum, a, b, c, d)
    return minimum, maximum


def get_maximum_value(expression):
    operations = expression[1::2]
    numbers = expression[::2]
    length = len(numbers)
    minima = [[0 for _ in range(length)] for _ in range(length)]
    maxima = [[0 for _ in range(length)] for _ in range(length)]
    for i in range(length):
        minima[i][i] = maxima[i][i] = int(numbers[i])
    for s in range(1, length):
        for i in range(length - s):
            j = i + s
            minima[i][j], maxima[i][j] = extrema(
                i, j, minima, maxima, operations)
    return maxima[0][-1]


if __name__ == "__main__":
    print(get_maximum_value(input()))
