function pathFinder(maze) {
    let grid = maze.split('\n').map(l => l.split(''));
    const n = grid.length;
    let dist = new Array(n).fill(0).map(l => new Array(n).fill(-1));
    let queue = [];
    let delta = [[0, 1], [0, -1], [1, 0], [-1, 0]];
    dist[0][0] = 0;
    queue.push([0, 0]);
    while(queue.length > 0) {
        const [x, y] = queue.shift();
        for(const [dx, dy] of delta) {
            let a = x + dx, b = y + dy;
            if(a < 0 || b < 0 || a >= n || b >= n || dist[a][b] != -1 || grid[a][b] != '.') continue;
            dist[a][b] = 1 + dist[x][y];
            queue.push([a, b]);
        }
    }
    return dist[n-1][n-1] == -1 ? false : dist[n-1][n-1];
}