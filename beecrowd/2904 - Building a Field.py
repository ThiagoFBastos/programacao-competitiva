from array import array	
	
n = int(input())

a = array('i', 2 * list(map(int, input().split())))
pre = array('q', [0] * (1 + len(a)))

for k in range(1, len(pre)):
	pre[k] = pre[k - 1] + a[k - 1]
	
s = pre[-1]

if s % 4:
	print('N')
	exit(0)

s //= 4
cnt = 0

i = 0

for k in range(1, n + 1):
	while i <= 2 * n and pre[i] - pre[k - 1] < s:
		i += 1
	if i <= 2 * n and pre[i] - pre[k - 1] == s:	
		cnt += 1

print('Y' if cnt >= 4 else 'N')