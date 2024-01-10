#!/usr/bin/env python3

from sys import stdin, stdout
from heapq import heapify, heappush, heappop

input, print = stdin.readline, stdout.write

def min_cycle(adj, st):
    n = len(adj)
    pq = []
    heapify(pq)
    d = [[-1, -1] for i in range(n)]
    heappush(pq, (0, st))
    while len(pq):
        cost, u = heappop(pq)
        if d[u][0] < 0:
            d[u][0] = cost
        elif d[u][1] < 0:
            d[u][1] = cost
        else:
            continue
        for v, w in adj[u]:
            if d[v][0] < 0 or d[v][1] < 0:
                heappush(pq, (cost + w, v))
    return d[st][1]
            
def main():
    n, m = map(int, input().split())

    adj = [[] for i in range(n)]

    for i in range(m):
        a, b, c = map(int, input().split())
        a, b = a - 1, b - 1
        adj[a].append((b, c))
    
    for v in range(n):
        print('%i\n'%min_cycle(adj, v))

if __name__ == '__main__':
    main()
