#include "bits/stdc++.h"

using namespace std;

void solve(int test) {
    int r, c;

    cin >> r >> c;

    vector<string> grid(r);
    vector<vector<int>> cnt(r);
    vector<vector<bool>> vis(r);
    int delta[][2] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    for(int i = 0; i < r; ++i) {
        cin >> grid[i];
        cnt[i].assign(c, 0);
        vis[i].assign(c, false);
    }

    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(vis[i][j] || grid[i][j] != 'W') continue;

            set<pair<int, int>> points;
            queue<pair<int, int>> q;
            int n = 0;

            q.emplace(i, j);
            vis[i][j] = true;

            while(!q.empty()) {
                auto [x0, y0] = q.front();
                q.pop();
                ++n;
                for(auto [dx, dy] : delta) {
                    int x1 = x0 + dx, y1 = y0 + dy;
                    if(x1 < 0 || x1 >= r || y1 < 0 || y1 >= c) continue;
                    if(grid[x1][y1] == '.') points.emplace(x1, y1);
                    if(vis[x1][y1] || grid[x1][y1] != 'W') continue;
                    vis[x1][y1] = true;
                    q.emplace(x1, y1);
                }
            }

            if((int)points.size() != 1) continue;
    
            auto [x, y] = *points.begin();

            cnt[x][y] += n;
        }
    }

    int ans {};

    for(auto& v : cnt) ans = max(ans, *max_element(v.begin(), v.end()));

    cout << "Case #" << test << ": " << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t = 1;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

