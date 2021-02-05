import sys


def get_change(money):
    coins = [4, 3, 1]

    table = [0] + [sys.maxsize for _ in range(money)]

    for i in range(1, money + 1):
        for j in range(len(coins)):
            if coins[j] <= i:
                num = table[i - coins[j]] + 1
                if num < table[i]:
                    table[i] = num

    return table[money]


if __name__ == '__main__':
    money = int(input())
    print(get_change(money))
