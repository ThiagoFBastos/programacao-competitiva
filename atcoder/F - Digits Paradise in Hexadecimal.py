#!/usr/bin/env python3

line = input().split()

n, k = line[0], int(line[1])

m = len(n)

fat = [0] * (max(16, m) + 1)
inv = [0] * (max(16, m) + 1)
invf = [0] * (max(16, m) + 1)

MOD = 10**9 + 7

for i in range(2):
	fat[i] = 1
	inv[i] = 1
	invf[i] = 1

for i in range(2, max(m, 16) + 1):
	fat[i] = i * fat[i - 1] % MOD
	inv[i] = (MOD - MOD // i) * inv[MOD % i] % MOD
	invf[i] = inv[i] * invf[i - 1] % MOD

def C(n, k):
	return fat[n] * invf[k] % MOD * invf[n - k] % MOD

def binExp(n, p, m):
	ans = 1
	while p > 0:
		if p & 1:
			ans = ans * n % m
		n = n * n % m
		p >>= 1
	return ans

memo = [[-1 for j in range(k + 1)] for i in range(m + 1)]
exp = [[1] * (m + 1)]

for i in range(1, k + 1):
	e = [1]
	for j in range(1, m + 1):
		e.append(e[-1] * i % MOD)
	exp.append(e)

def countKdigits(l, Z, Z_need):
	if memo[l][Z_need] != -1:
		return memo[l][Z_need]
	Z -= Z_need
	dp = exp[k][l]
	for i in range(0, Z_need):
		total = C(Z_need, i) * exp[Z + i][l]
		if (Z_need - i) & 1:
			total *= -1
		dp += total
		if dp >= MOD:
			dp -= MOD
		elif dp < 0:
			dp += MOD
	memo[l][Z_need] = dp
	return dp

def alpha(c):
	asc = ord(c)
	return asc - ord('0') if ord('0') <= asc <= ord('9') else asc - ord('A') + 10

frq = [0] * 16
digits = 0
ans = 0

for i in range(m):
	d = alpha(n[i])

	min_digit = 1 if i == 0 else 0

	for j in range(min_digit, d):
		frq[j] += 1

		if frq[j] == 1: 
			digits += 1
		
		if digits <= k and m - i - 1 >= k - digits:
			ans += countKdigits(m - i - 1, k, k - digits) * C(16 - digits, k - digits)		
			ans %= MOD
			
		frq[j] -= 1
		
		if frq[j] == 0:
			digits -= 1
	
	frq[d] += 1

	if frq[d] == 1:
		digits += 1

if digits == k:
	ans += 1
	ans %= MOD

for l in range(1, m):
	if l < k:
		continue
	ans += 15 * countKdigits(l - 1, k, k - 1) * C(15, k - 1)
	ans %= MOD

print(ans)
