#!/usr/bin/env python3

from sys import stdin, stdout
from math import inf

input, print = stdin.readline, stdout.write

def find_bounds(p):
    n = len(p)
    bit = [[-inf, -inf] for i in range(n + 1)]
    ans = [[] for i in range(n)]

    def upd(k, x):
        k += 1
        while k <= n:
            if x > bit[k][0]:
                bit[k][1] = bit[k][0]
                bit[k][0] = x
            else:
                bit[k][1] = max(bit[k][1], x)
            k += k & -k

    def query(k):
        ans = [-inf, -inf]
        k += 1
        while k > 0:
            if bit[k][0] > ans[0]:
                ans[1] = max(bit[k][1], ans[0])
                ans[0] = bit[k][0]
            else:
                ans[1] = max(ans[1], bit[k][0])
            k -= k & -k
        return ans

    for i in range(n):
        ans[i] = query(n - p[i])
        upd(n - p[i], i)

    return ans

def main():
    
    n = int(input())
    p = list(map(int, input().split()))

    lo = find_bounds(p)

    p.reverse()

    hi = find_bounds(p)

    p.reverse()
    hi.reverse()

    for i in range(n):
        hi[i][0] = n - hi[i][0] - 1
        hi[i][1] = n - hi[i][1] - 1

    ans = 0

    for i in range(n):
        lo1 = max(0, lo[i][1] + 1)
        lo2 = max(-1, lo[i][0])
        hi1 = min(n, hi[i][0])
        hi2 = min(n - 1, hi[i][1] - 1)

        if lo2 > -1:
            ans += (lo2 - lo1 + 1) * (hi1 - i) * p[i]

        if hi1 < n:
            ans += (i - lo2) * (hi2 - hi1 + 1) * p[i]

    print('%i\n' % ans)

if __name__ == '__main__':
    main()
