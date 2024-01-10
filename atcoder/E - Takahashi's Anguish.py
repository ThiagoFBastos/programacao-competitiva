#!/usr/bin/env python3

from sys import stdin, stdout
from math import inf

input, print = stdin.readline, stdout.write

def main():
    
    n = int(input())
    x = list(map(int, input().split()))
    c = list(map(int, input().split()))
    
    vis = [-1] * n
    lst = []

    ans = 0
    
    for i in range(n):
        if vis[i] != -1: continue

        min_c = inf
        lo = len(lst)

        while vis[i] < 0:
            vis[i] = len(lst)
            lst.append(i)
            i = x[i] - 1

        u = lst[-1]

        if vis[x[u]-1] >= lo:
            for u in lst[vis[x[u] - 1] : ]:
                min_c = min(min_c, c[u])
            ans += min_c

    print('%i\n'%ans)
    
if __name__ == '__main__':
    main()
