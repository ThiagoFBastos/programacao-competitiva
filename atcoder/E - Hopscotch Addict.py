#!/usr/bin/env python3

from collections import deque

n, m = map(int, input().split())

adj = [[] for i in range(n+1)]
d = [[-1,-1,-1] for i in range(n+1)]
q = deque()

for i in range(m):
	u, v = map(int, input().split())
	adj[u].append(v)

s, t = map(int, input().split())

d[s][0] = 0
q.append((s, 0))

while len(q):
	u, k = q.popleft()
	for v in adj[u]:
		if d[v][(k + 1) % 3] != -1:
			continue
		d[v][(k+1)%3] = d[u][k] + 1
		q.append((v, (k+1)%3))

if d[t][0] != -1:
	print(d[t][0] // 3)
else:
	print(-1)
