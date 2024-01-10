#!/usr/bin/env python3

INF = 10**9
n, m = map(int, input().split())
cost = [INF] * (1<<n)

for i in range(m):
	a, b = map(int, input().split())
	S = 0
	c = list(map(int,input().split()))
	for v in c: S |= 1<<(v-1)
	cost[S] = min(cost[S],a)

for i in reversed(range(1<<n)):
	for j in range(n):
		if i & (1<<j):
			cost[i^(1<<j)] = min(cost[i],cost[i^(1<<j)])

for i in range(1<<n):
	j = i
	while j:	
		cost[i] = min(cost[i], cost[i^j]+cost[j])
		j = i & (j - 1)

print(-1 if cost[-1] >= INF else cost[-1])


