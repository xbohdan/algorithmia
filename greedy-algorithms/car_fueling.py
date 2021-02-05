import sys


def compute_min_refills(distance, tank, stops):
    num = 0
    limit = tank
    current = 0
    while limit < distance:
        if current >= len(stops) or stops[current] > limit:
            return -1
        while current < len(stops) - 1 and stops[current + 1] <= limit:
            current += 1
        num += 1
        limit = stops[current] + tank
        current += 1
    return num


if __name__ == '__main__':
    distance, tank, _, *stops = map(int, sys.stdin.read().split())
    print(compute_min_refills(distance, tank, stops))
