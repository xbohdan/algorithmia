def edit_distance(source, target):
    if len(source) < len(target):
        return edit_distance(target, source)

    if len(target) == 0:
        return len(source)

    prev = range(len(target) + 1)
    for i, s in enumerate(source):
        curr = [i + 1]
        for j, t in enumerate(target):
            insertions = prev[j + 1] + 1
            deletions = curr[j] + 1
            substitutions = prev[j] + (s != t)
            curr.append(min(insertions, deletions, substitutions))
        prev = curr

    return curr[-1]


if __name__ == "__main__":
    print(edit_distance(input(), input()))
