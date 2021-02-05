import sys


def get_change(money):
    coins = [10, 5, 1]

    num = 0

    for coin in coins:
        num += money // coin
        money %= coin

    return num


if __name__ == '__main__':
    money = int(sys.stdin.read())
    print(get_change(money))
