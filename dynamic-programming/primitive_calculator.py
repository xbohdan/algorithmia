def optimal_sequence(n):
    nums = [None] * (n + 1)
    ops = [0] + [None] * n

    for i in range(1, n + 1):
        num1 = i - 1
        op1 = ops[num1] + 1

        if i % 3 == 0:
            num2 = i // 3
            op2 = ops[num2] + 1
            if op2 < op1:
                num1, op1 = num2, op2

        if i % 2 == 0:
            num2 = i // 2
            op2 = ops[num2] + 1
            if op2 < op1:
                num1, op1 = num2, op2

        nums[i], ops[i] = num1, op1

    seq = []
    while n > 0:
        seq.append(n)
        n = nums[n]

    return reversed(seq)


n = int(input())
seq = list(optimal_sequence(n))
print(len(seq))
for i in seq:
    print(i, end=' ')
