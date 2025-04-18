#!/usr/bin/env python3

import heapq

while True:
	n, m, c, k = map(int, input().split())
	
	if n + m + c + k == 0:
		break

	adj = [[] for i in range(n)]
	cost = [[-1, -1] for i in range(n)]
	nxt = [-1] * n

	for i in range(m):
		a, b, w = map(int, input().split())
		if a > b:
			a, b = b, a
		adj[a].append((b, w))
		adj[b].append((a, w))
		if b < c and a + 1 == b:
			nxt[a] = w
	
	pq = []
	heapq.heapify(pq)

	heapq.heappush(pq, (0, 0, k))

	while len(pq):
		ct, t, u = heapq.heappop(pq)

		if cost[u][t] != -1:
			continue

		cost[u][t] = ct

		if u < c - 1:
			if cost[u + 1][1] == -1:
				heapq.heappush(pq, (ct + nxt[u], 1, u + 1))
		else:
			for (v, w) in adj[u]:
				nt = 1 if v < c else 0
				if cost[v][nt] != -1:
					continue
				heapq.heappush(pq, (ct + w, nt, v))

	print(cost[c - 1][1])
	
	