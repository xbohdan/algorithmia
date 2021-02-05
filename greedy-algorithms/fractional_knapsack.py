import sys


def get_optimal_value(capacity, values, weights):
    value_per_unit = sorted(zip(values, weights),
                            key=lambda x: x[0] / x[1], reverse=True)
    value = 0

    for v, w in value_per_unit:
        if capacity == 0:
            break
        weight = min(capacity, w)
        value += v / w * weight
        capacity -= weight

    return value


if __name__ == "__main__":
    data = list(map(int, sys.stdin.read().split()))
    n, capacity = data[0:2]
    values = data[2:(2 * n + 2):2]
    weights = data[3:(2 * n + 2):2]
    opt_value = get_optimal_value(capacity, values, weights)
    print("{:.10f}".format(opt_value))
