#!/usr/bin/env python3
 
 
def f(n):
	return n * (n + 1) // 2
 
n = int(input())
 
r = list(map(int, input().split()))
 
ans = 0.0
 
for i in range(len(r)):
	for j in range(i + 1, len(r)):
		ans += (max(0, r[i] - r[j]) * r[j] + f(min(r[i], r[j]) - 1)) * 10**6 / (r[i] * r[j])
 
print('{0:6f}'.format(ans / 10**6))
 
