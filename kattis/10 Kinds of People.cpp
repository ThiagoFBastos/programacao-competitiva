#include "bits/stdc++.h"
using namespace std;
void solve() {
    int r, c, q, id = 0;
    cin >> r >> c;
    vector<string> g(r);
    vector<vector<int>> cc(r, vector<int>(c, -1));
    for(int i = 0; i < r; ++i) cin >> g[i];
    function<void(int, int, char)> dfs = [&](int x, int y, char ch) {
        if(x < 0 || y < 0 || x >= r || y >= c || cc[x][y] != -1 || g[x][y] != ch) return;
        cc[x][y] = id;
        dfs(x - 1, y, ch);
        dfs(x + 1, y, ch);
        dfs(x, y - 1, ch);
        dfs(x, y + 1, ch);
    };
    for(int i = 0; i < r; ++i) {
        for(int j = 0; j < c; ++j) {
            if(cc[i][j] != -1) continue;
            dfs(i, j, g[i][j]);
            ++id;
        }
    }
    cin >> q;
    while(q--) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        --x0, --y0, --x1, --y1;
        if(cc[x0][y0] != cc[x1][y1]) cout << "neither\n";
        else cout << (g[x0][y0] - '0' ? "decimal\n" : "binary\n");
    }
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}