#!/usr/bin/env python3

t = int(input())
input()

for i in range(t):
	trees = []
	
	while True:
		try:
			specie = input()
			
			if specie == '':
				break

			trees.append(specie)
		except EOFError:
			break

	n = len(trees)
	cnt = [0] * n
	trees.sort()

	cnt[0] = 1
	for j in range(1, n):
		cnt[j] = 1 + cnt[j - 1] if trees[j] == trees[j - 1] else 1

	for j in range(n):		
		if j == n - 1 or trees[j] != trees[j + 1]:
			print('{} {:.4f}'.format(trees[j], 100 * cnt[j] / n))

	if i < t - 1: print()