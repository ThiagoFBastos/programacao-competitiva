#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e2 + 5, K = 21;

int dp[N][N][K][K][2], grid[N][N];

struct CostData {
    short r;
    short c;
    char x;
    char y;
    char t;

    CostData() = default;

    CostData(short _r, short _c, char _x, char _y, char _t)
        : r(_r)
        , c(_c)
        , x(_x)
        , y(_y)
        , t(_t)
    {

    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, x, y;

    pair<int, int> delta[] = {{1, 0}, {0, -1}, {0, 1}};

    constexpr int INF = numeric_limits<int>::max();

    while(cin >> n >> m >> x >> y) {

        int min_negative_element {};

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                cin >> grid[i][j];
                min_negative_element = min(min_negative_element, grid[i][j]);
            }
        }

        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                for(int k = 0; k <= x; ++k)
                    for(int l = 0; l <= y; ++l)
                        for(int t = 0; t < 2; ++t)
                            dp[i][j][k][l][t] = INF;

        auto fix = [min_negative_element](int value) {
            if(value < 0)
                value -= min_negative_element;
            return value;
        };

        const int MAXVALUE = n * m * 100;
    
        vector<vector<CostData>> pq(MAXVALUE + 1);

        int xc = grid[0][0] == 0;
        int yc = grid[0][0] < 0;

        pq[fix(grid[0][0])].emplace_back(0, 0, xc, yc, 1);
        dp[0][0][xc][yc][1] = fix(grid[0][0]);

        int cur = 0;
        while(cur <= MAXVALUE) {
            if(pq[cur].empty()) {
                ++cur;
                continue;
            }

            auto [r, c, xc, yc, t] = pq[cur].back();

            pq[cur].pop_back();

            if(dp[r][c][xc][yc][t] != cur)
                continue;

            for(int i = 0; i < 3; ++i) {
                auto [dx, dy] = delta[i];
                int r_dest = r + dx;
                int c_dest = c + dy;

                if(r_dest < 0 || c_dest < 0 || r_dest >= n || c_dest >= m)
                    continue;

                int x_dest = xc + (grid[r_dest][c_dest] == 0);
                int y_dest = yc + (grid[r_dest][c_dest] < 0);

                if(r_dest > r) {
                    for(int t_dest : {0, 1}) {
                        int new_cost = cur + fix(grid[r_dest][c_dest]);

                        if(x_dest > x || y_dest > y || dp[r_dest][c_dest][x_dest][y_dest][t_dest] <= new_cost)
                            continue;

                        dp[r_dest][c_dest][x_dest][y_dest][t_dest] = new_cost;
                        pq[new_cost].emplace_back(r_dest, c_dest, x_dest, y_dest, t_dest);
                    }
                } else if(t == i - 1) {
                    
                    int new_cost = cur + fix(grid[r_dest][c_dest]);

                    if(x_dest > x || y_dest > y || dp[r_dest][c_dest][x_dest][y_dest][t] <= new_cost)
                        continue;

                    dp[r_dest][c_dest][x_dest][y_dest][t] = new_cost;
                    pq[new_cost].emplace_back(r_dest, c_dest, x_dest, y_dest, t);
                }
            }
        }

        optional<int> answer;

        for(int i = 0; i <= x; ++i) {
            for(int j = 0; j <= y; ++j) {
                for(int t : {0, 1}) {
                    if(dp[n - 1][m - 1][i][j][t] == INF)
                        continue;

                    int cost = dp[n - 1][m - 1][i][j][t] + j * min_negative_element;

                    answer = min(answer.value_or(INF), cost);
                }
            }
        }

        if(answer)
            cout << *answer << '\n';
        else
            cout << "Impossivel\n";
    }

    return 0;
}