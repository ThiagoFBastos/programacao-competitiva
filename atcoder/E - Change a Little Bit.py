#!/usr/bin/env python3

from sys import stdin, stdout

input, print = stdin.readline, stdout.write

def main():
    n = int(input())
    c = sorted(list(map(int, input().split())))

    pw = [0] * (2 * n + 1)
    MOD = 10 ** 9 + 7
    pw[0] = 1

    for i in range(1, 2 * n + 1): pw[i] = 2 * pw[i - 1] % MOD

    ans = 0

    for i in range(n):
        ans = (ans + c[i] * pw[2 * (n - 1)] * 2) % MOD
     
        if n - i - 1 > 0:
            ans = (ans + c[i] * pw[2 * (n - 2)] * 4 % MOD * (n - i - 1)) % MOD

    print('%i\n' % ans)

if __name__ == '__main__':
    main()
