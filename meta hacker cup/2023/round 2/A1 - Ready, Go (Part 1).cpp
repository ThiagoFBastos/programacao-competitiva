#include "bits/stdc++.h"

using namespace std;

bool hasGroup(vector<string>& grid) {
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<bool>> vis(r);

    int delta[][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    for(int i = 0; i < r; ++i) vis[i].assign(c, false);

    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(vis[i][j] || grid[i][j] != 'W') continue;

            queue<pair<int, int>> q;

            bool empt {};

            q.emplace(i, j);

            vis[i][j] = true;

            while(!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                empt = empt || grid[x][y] == '.';
                for(auto [dx, dy] : delta) {
                    int xt = x + dx, yt = y + dy;
                    if(xt < 0 || xt >= r || yt < 0 || yt >= c || vis[xt][yt] || grid[xt][yt] == 'B') continue;
                    vis[xt][yt] = true;
                    q.emplace(xt, yt);
                }
            }

            if(!empt) return true;
        }
    }

    return false;
}

void solve(int test) {
    int r, c;

    cin >> r >> c;

    vector<string> grid(r);

    for(auto& s : grid) cin >> s;

    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(grid[i][j] != '.') continue;

            grid[i][j] = 'B';

            if(hasGroup(grid)) {
                cout << "Case #" << test << ": YES\n";  
                return;
            }

            grid[i][j] = '.';
        }
    }

    cout << "Case #" << test << ": NO\n";  
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t = 1;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

