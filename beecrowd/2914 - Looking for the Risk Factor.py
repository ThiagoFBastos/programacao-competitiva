from array import array

maxn = 0
q = int(input())
v = [(0, 0, 0)] * q
ans = array('i', [0] * q)

for i in range(q):
	n, k = map(int, input().split()) 
	v[i] = n, k, i
	if n > maxn:
		maxn = n
		
maxn += 1
fator = array('i', [0] * maxn)
bit = array('i', [0] * maxn)

def upd(k, x):
	while k < maxn:
		bit[k] += x
		k += k & -k
		
def query(k):
	v = 0
	k = min(k, maxn - 1)
	while k > 0:
		v += bit[k]
		k -= k & -k
	return v

for k in range(2, maxn):
	if fator[k] > 0:
		continue
	for i in range(k, maxn, k):
		fator[i] = k
		
v.sort()

i = 0

for k in range(2, maxn):
	upd(fator[k], 1)
	while i < q and v[i][0] == k:
		ans[v[i][2]] = query(v[i][1])
		i += 1
	
for v in ans:
	print(v)