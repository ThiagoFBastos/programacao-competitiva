#!/usr/bin/env pypy3

from sys import stdin, stdout

input, print = stdin.readline, stdout.write

class uf:
	def __init__(self, n):
		self.par = list(range(n))
		self.rank = [0] * n
	
		
	def __findSet(self, u):
		if u == self.par[u]:
			return u
		self.par[u] = self.__findSet(self.par[u])
		return self.par[u]

	def join(self, u, v):
		u = self.__findSet(u)
		v = self.__findSet(v)

		if u == v:
			return

		self.par[u] = v
		
		if self.rank[u] == self.rank[v]:
			self.rank[v] += 1

	def same(self, u, v):
		return self.__findSet(u) == self.__findSet(v)
		

n, q = map(int, input().split())

dsu = uf(n + 1)

for c in range(q):
	l, r = map(int, input().split())
	dsu.join(l - 1, r)

if dsu.same(0, n):
	print('Yes\n')
else:
	print('No\n')
