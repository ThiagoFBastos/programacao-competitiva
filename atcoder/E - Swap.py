#!/usr/bin/env python3

from sys import stdin, stdout

input, print = stdin.readline, stdout.write

def main():
    s = input().replace('\n', '')
    lim = int(input())

    K = []
    E = []
    Y = []

    for i, ch in enumerate(s):
        if ch == 'K': K.append(i)
        elif ch == 'E': E.append(i)
        else: Y.append(i)

    n = len(s)

    dp = []

    for i in range(len(K) + 1):
        v_i = []
        for j in range(len(E) + 1):
            v_j = []
            for k in range(len(Y) + 1):
                v_j.append([0] * (n * n + 1))
            v_i.append(v_j)
        dp.append(v_i)

    dp[0][0][0][0] = 1

    lt = [[[[0] * (n + 1) for k in range(n + 1)] for j in range(3)] for i in range(3)]

    arr = [K, E, Y]

    for i in range(3):
        for j in range(3):
            if i == j:
                continue
            A, B = arr[i], arr[j]
            for a in range(len(A)):
                cur = 0
                for b in reversed(range(len(B))):
                    if A[a] > B[b]:
                        cur += 1
                    lt[i][j][a][b] = cur

    for i in range(len(K) + 1):
        for j in range(len(E) + 1):
            for k in range(len(Y) + 1):
                for swaps in range(n * n + 1):

                    if i < len(K):
                        f = lt[0][1][i][j] + lt[0][2][i][k]
                        if swaps + f <= n * n:
                            dp[i+1][j][k][swaps+f] += dp[i][j][k][swaps]

                    if j < len(E):
                        f = lt[1][0][j][i] + lt[1][2][j][k]
                        if swaps + f <= n * n:
                            dp[i][j + 1][k][swaps + f] += dp[i][j][k][swaps]

                    if k < len(Y):
                        f = lt[2][0][k][i] + lt[2][1][k][j]
                        if swaps + f <= n * n:
                            dp[i][j][k + 1][swaps + f] += dp[i][j][k][swaps]

    ans = 0
    for i in range(min(n*n, lim) + 1):
        ans += dp[-1][-1][-1][i]

    print('%i\n' % ans)
                    

if __name__ == '__main__':
    main()
