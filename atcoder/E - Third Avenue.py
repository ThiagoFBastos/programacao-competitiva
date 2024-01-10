#!/usr/bin/env python3

from sys import stdin, stdout
from collections import deque

input, print = stdin.readline, stdout.write

def main():

    h, w = map(int, input().split())
    
    grid = [input() for i in range(h)]
    d = [[-1] * w for i in range(h)]

    Z = [[] for i in range(26)]
    Z_d = [-1] * 26

    x_from, y_from = -1, -1

    for i in range(h):
        for j in range(w):

            if grid[i][j] == 'S':   
                x_from, y_from = i, j
            else:
                asc = ord(grid[i][j]) - 97
                if asc >= 0 and asc <= 25:
                    Z[asc].append((i, j))

    qxy = deque()
    qc = deque()

    d[x_from][y_from] = 0
    qxy.append((0, x_from, y_from))

    delta = [[1, 0], [0, 1], [-1, 0], [0, -1]]

    while len(qxy) + len(qc):

        is_qxy = None

        if len(qxy) and len(qc):
            dxy, x, y = qxy.popleft()
            dc, c = qc.popleft()
            is_qxy = dxy < dc
            qxy.appendleft((dxy, x, y))
            qc.appendleft((dc, c))
        elif len(qxy):
            is_qxy = True
        else:
            is_qxy = False

        
        if is_qxy:
            dxy, x, y = qxy.popleft()

            if grid[x][y] == 'G':
                print('%i\n' % (dxy, ))
                return

            ch = ord(grid[x][y]) - 97

            if ch >= 0 and ch <= 25 and Z_d[ch] < 0:
                Z_d[ch] = d[x][y] + 1
                qc.append((Z_d[ch], ch))

            for dx, dy in delta:
                i, j = x + dx, y + dy
                if i < 0 or j < 0 or i >= h or j >= w or grid[i][j] == '#' or d[i][j] != -1: continue
                d[i][j] = d[x][y] + 1
                qxy.append((d[i][j], i, j))
        else:
            dc, c = qc.popleft()

            for i, j in Z[c]:
                if d[i][j] < 0:
                    d[i][j] = dc
                    qxy.appendleft((dc, i, j))

    print('-1\n')
   
if __name__ == '__main__':
    main()
