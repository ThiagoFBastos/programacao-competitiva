function pathFinder(maze){
    let grid = maze.split('\n').map(s => s.split(''));
    let n = grid.length;
    let dfs = (x, y) => {
        if(x < 0 || y < 0 || x >= n || y >= n || grid[x][y] == 'W') return false;
        if(x == n - 1 && y == n - 1) return true;
        grid[x][y] = 'W';
        return dfs(x - 1, y) || dfs(x + 1, y) || dfs(x, y - 1) || dfs(x, y + 1);
    };
    return dfs(0, 0);
}