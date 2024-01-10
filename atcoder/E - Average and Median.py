#!/usr/bin/env python3

from sys import stdin, stdout
from math import inf

input, print = stdin.readline, stdout.write

def max_mean(A):
    lo, hi = 1, 10 ** 9
    for i in range(64):
        mid = (lo + hi) / 2
        f0, f1 = -inf, 0
        for a in A:
            f0, f1 = f1, max(f0, f1) + a - mid
        if max(f0, f1) >= 0:
            lo = mid
        else:
            hi = mid
    return hi

def max_median(A):
    lo, hi = 1, 10 ** 9 + 1
    while lo < hi:
        mid = (lo + hi) // 2
        f0, f1 = -inf, 0
        for a in A:
            f0, f1 = f1, (1 if a >= mid else -1) + max(f0, f1)
        if max(f0, f1) <= 0:
            hi = mid
        else:
            lo = mid + 1
    return hi - 1

def main():
    n = int(input())
    A = list(map(int, input().split()))
    
    print('%.9f\n'%max_mean(A))
    print('%i\n'%max_median(A))
   
if __name__ == '__main__':
    main()
