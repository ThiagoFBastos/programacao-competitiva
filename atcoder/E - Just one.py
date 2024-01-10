#!/usr/bin/env python3

from sys import stdin, stdout
from collections import deque

input, print = stdin.readline, stdout.write

def dfs(adj, u, vis):
    st = deque()
    st.append((u, 0))
    vis[u] = True
    n, m = 1, len(adj[u])
    while len(st):
        u, cur = st.pop()
        if cur < len(adj[u]):
            v = adj[u][cur]
            if not vis[v]:
                vis[v] = True
                n += 1
                m += len(adj[v])
                st.append((v, 0))
        if cur + 1 < len(adj[u]):
            st.append((u, cur + 1))
    return n == m // 2

def main():
    n, m = map(int, input().split())

    adj = [[] for i in range(n)]

    for i in range(m):
        a, b = map(int, input().split())
        a, b = a - 1, b - 1
        adj[a].append(b)
        adj[b].append(a)

    if n != m:
        print('0\n')
        return

    MOD = 998244353
    ans = 1
    vis = [False] * n
   
    for i in range(n):
        if vis[i]: continue
        elif dfs(adj, i, vis):
            ans <<= 1
            ans %= MOD
        else:
            print('0\n')
            return

    print('%i\n'%ans)
            
    
if __name__ == '__main__':
    main()
