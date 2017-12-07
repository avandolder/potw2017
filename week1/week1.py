# POTW 2017 Week 1 - Squirrel Frenzy
# Adam Vandolder

from math import ceil

# Process the input
n = int(input())
holes = [int(x) for x in input().split()]
c, s = (int(x) for x in input().split())

# Construct a list containing the number of holes with h chestnuts in them.
holes_with_h = [0 for x in range(51)]
max_h = holes[0]
for i in holes:
    holes_with_h[i] += 1

    # Keep track of the maximum number of chestnuts in a hole.
    if i > max_h:
        max_h = i

# print(c, s, holes)
# print(max_n, floor(s/2), holes_with_n[:max_n+1])

# Calculate the number of unique pairs of holes summing to exactly S.
pairs = 0
# Loop from half of S to the maximum number of chestnuts in a single hole.
for i in range(ceil(s/2), max_h+1):
    if s - i == i:
        # If i is exactly half of s, then all holes with i chestnuts form
        # unique pairs with all other holes with i chestnuts. This results
        # in a number of pairs equal to the sum of 1 to n, or n*(n+1) / 2.
        n = holes_with_h[i] - 1
        pairs += int(n * (n + 1) / 2)
    else:
        pairs += holes_with_h[s - i] * holes_with_h[i]

    if pairs >= c:
        break

    # print(i, s-i, holes_with_h[i], holes_with_h[s - i], pairs)

if pairs >= c:
    print("True") #, pairs)
else:
    print("False") #, pairs)
