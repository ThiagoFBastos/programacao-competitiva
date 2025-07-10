#!/usr/bin/env python3

from math import inf

def floyd_warshall(dist, n):
    for k in range(n):
        for i in range(n):
            for j in range(n):
                dist[i*n+j] = min(dist[i*n+j], dist[i*n+k] + dist[k*n+j])
def main():
    while True:
        n, m, q = map(int, input().split())
        
        if n + m + q == 0:
            break

        dist = []

        for i in range(n):
            for j in range(n):
                dist.append(inf if i != j else 0)

        for i in range(m):
            u, v, w = map(int, input().split())
            dist[u*n+v] = min(dist[u*n+v], w)

        floyd_warshall(dist, n)

        dist2 = dist.copy()

        floyd_warshall(dist2, n)
        
        for i in range(q):
            u, v = map(int, input().split())

            if dist[u*n+v] == inf:
                print('Impossible')
            elif dist[u*n+v] > dist2[u*n+v]:
                print('-Infinity')
            else:
                print(dist[u*n+v])

        print()

if __name__ == '__main__':
    main()