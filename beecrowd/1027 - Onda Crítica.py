#!/usr/bin/env python3

from array import array

up = array('i', [0] * 1000)
down = array('i', [0] * 1000)

while True:
	try:
		n = int(input())
		v = [(0, 0)] * n
		
		for k in range(n):
			x, y = map(int, input().split())
			v[k] = (x, y)
			
		v.sort()
		
		S = dict()
		
		ans = 0
		
		for k in range(n):
		
			if k > 0 and v[k] == v[k - 1]:
				continue
			
			x, y = v[k]	
			up[k], down[k] = 1, 1
			
			a = S.get(y - 2, None)
			
			if a != None:
				i = a[-1]
				if x != v[i][0]:
					up[k] = down[i] + 1
				elif len(a) > 1:
					up[k] = down[a[0]] + 1
					
			a = S.get(y + 2, None)
			
			if a != None:
				i = a[-1]
				if x != v[i][0]:
					down[k] = up[i] + 1
				elif len(a) > 1:
					down[k] = up[a[0]] + 1
					
			b = S.get(y, None)
			
			if b == None:
				S[y] = [k]
			else:
				b.append(k)
				if len(b) > 2:
					del b[0]
					
			ans = max(ans, max(down[k], up[k]))
			
		print(ans)
		
	except EOFError:
		break