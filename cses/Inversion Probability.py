from decimal import Decimal, getcontext
 
getcontext().prec = 50
 
def f(n):
	return n * (n + 1) // 2
 
n = int(input())
 
r = list(map(int, input().split()))
 
ans = Decimal('0')
 
for i in range(len(r)):
	for j in range(i + 1, len(r)):
		ans += Decimal((max(0, r[i] - r[j]) * r[j] + f(min(r[i], r[j]) - 1))) / Decimal(r[i] * r[j])
 
print('{:.6f}'.format(ans))