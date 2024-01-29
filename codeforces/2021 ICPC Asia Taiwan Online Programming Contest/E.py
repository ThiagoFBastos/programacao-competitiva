#!/usr/bin/env python3

p, q = map(int, input().split())
X = 0
Y = 0

for k in range(3983):
	Y += k * k * k * k * k
	Z = (k + 1) * p - q * Y
	if X < Z:
		X = Z
	if p <= q * k * k * k * k * k:
		break

lo = 1
hi = 10 ** 17
R = 10 ** 99

while lo < hi:
	mid = (lo + hi) // 2
	L = q * mid ** 2 * (mid + 1) ** 2 * (2 * mid ** 2 + 2 * mid - 1) // 12 + X - p * mid
	if L >= R:
		hi = mid
	else:	
		lo = mid + 1

print(X)
print(hi)
	

