#!/usr/bin/env python3

from math import log

s = input()
l = len(s)
i = 0

if s == "0":
	print(1)
else:
	while i * log(6) / log(10) + 1 < l:
		i += 1

	for k in range(2):
		p = str(6 ** i)

		if len(p) == l and p <= s:
			i += 1

	print(i)

