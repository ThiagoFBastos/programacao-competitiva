#!/usr/bin/env python3

import heapq
from sys import stdout, stdin, exit

print, input = stdout.write, stdin.readline

n, m, s = map(int, input().split())

adj = [[] for u in range(n)]

for i in range(m):
    u, v, t0, p, d = map(int, input().split())
    adj[v].append((u, t0, p, d))

pq = []
time = [-1] * n
max_time = [-1] * n

heapq.heapify(pq)

heapq.heappush(pq, (-s, n - 1))

while len(pq):
    curt, v = heapq.heappop(pq)

    if time[v] != -1: continue

    curt *= -1
    time[v] = curt

    for u, t0, p, d in adj[v]:
        if time[u] != -1: continue

        t = curt - d

        t -= abs(t - t0) % p

        if t < t0: continue

        heapq.heappush(pq, (-t, u))

if time[0] == -1:
    print('impossible\n')
    exit(0)

print(f'{time[0]}\n')
