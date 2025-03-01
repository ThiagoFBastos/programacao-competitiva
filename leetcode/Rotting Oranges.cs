public class Solution {
    public int OrangesRotting(int[][] grid) {
        int m = grid.Length, n = grid[0].Length, cells = 0;
        int[,] time = new int[m, n];
        int[,] delta = new int[4, 2] {
            {-1, 0},
            {1, 0},
            {0, -1},
            {0, 1}
        };
        var queue = new Queue<KeyValuePair<int, int>>();

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                time[i, j] = -1;
                cells += grid[i][j] != 0 ? 1 : 0;
                if(grid[i][j] == 2) {
                    time[i, j] = 0;
                    queue.Enqueue(new KeyValuePair<int, int>(i, j));
                }
            }
        }

        int lastTime = 0;

        while(queue.Count > 0) {
            var pos = queue.Dequeue();
            int x0 = pos.Key, y0 = pos.Value;

            if(lastTime < time[x0, y0])
                lastTime = time[x0, y0];

            --cells;

            for(int i = 0; i < 4; ++i) {
                int x = x0 + delta[i,0], y = y0 + delta[i,1];
                if(x < 0 || y < 0 || x >= m || y >= n || grid[x][y] == 0 || time[x, y] != -1) continue;
                time[x, y] = 1 + time[x0, y0];
                queue.Enqueue(new KeyValuePair<int, int>(x, y));
            }
        }

        if(cells > 0)
            return -1;

        return lastTime;
    }
}