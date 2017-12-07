# potw week 2
n = int(input())
p = [int(x) for x in input().split()]
l, r = (int(x) for x in input().split())

found = False
for i in range(len(p)):
    left = (l + sum(p[:i])) / (1 + len(p[:i]))
    right = (r + sum(p[i+1:])) / (1 + len(p[i+1:]))

    # print(l, p[:i], left)
    # print(r, p[i+1:], right)
    # print(1 - (p[i] / left), 1 - (p[i] / right))

    if 1 - (p[i] / left) >= 0.15 and 1 - (p[i] / right) >= 0.15:
        print(i)
        found = True
        break

if not found:
    print(-1)
