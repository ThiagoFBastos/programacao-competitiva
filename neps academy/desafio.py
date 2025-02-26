def modMulExp(a, p, m):
	ans = 1
	while p > 0:
		if p & 1:
			ans = ans * a % m
		a = a * a % m
		p >>= 1
	return ans

def miller(n):
	P = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
	
	for p in P:
		if n % p == 0:
			return n == p

	if n < P[-1]:
		return False

	s, t = 0, n - 1

	while ~t & 1:
		t >>= 1
		s += 1

	for p in P:
		pt = modMulExp(p, t, n)
		if pt == 1:
			continue		
		ok = False
		for j in range(s):
			if ok:
				break
			elif pt == n - 1:
				ok = True
			pt = pt * pt % n
		if not ok:
			return False

	return True

if __name__ == "__main__":
	n = int(input())

	if miller(n):
		print('talvez')
	else:
		print('definitivamente nao primo')


