#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e2 + 5, M = 8;

int dist[1 << M][N][N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, w, h;

    pair<int, int> delta[] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    while(cin >> n >> m >> w >> h) {
        auto view = views::iota(0, h) | views::transform([](auto) {
            string row;
            cin >> row;
            return row;
        });

        vector<string> grid;
        queue<tuple<int, int, int>> q;
        vector<pair<int, int>> dust;

        ranges::copy(view, back_inserter(grid));

        optional<pair<int, int>> start, finish;

        ranges::for_each(views::iota(0, h), [&](auto r) {
            ranges::for_each(views::iota(0, w), [&](auto c) {
                if(grid[r][c] == 'R')
                    start = make_pair(r, c);
                else if(grid[r][c] == 'S')
                    finish = make_pair(r, c);
                else if(grid[r][c] == '*')
                    dust.emplace_back(r, c);

                for(int i = 0; i < (1 << n); ++i)
                    dist[i][r][c] = -1;
            });
        });

        assert(start && finish);

        sort(dust.begin(), dust.end());

        auto [x0, y0] = *start;

        dist[0][x0][y0] = 0;
        q.emplace(0, x0, y0);

        while(!q.empty()) {
            auto [mask, x, y] = q.front();

            q.pop();

            int d = dist[mask][x][y];

            if(d == m)
                continue;

            for(auto [dx, dy] : delta) {
                int xto = x + dx, yto = y + dy, maskto = mask;
                
                if(xto < 0 || xto >= h || yto < 0 || yto >= w || grid[xto][yto] == '#') continue;

                auto it = find(dust.begin(), dust.end(), make_pair(xto, yto));

                if(it != dust.end() && *it == make_pair(xto, yto))
                    maskto |= 1 << static_cast<int>(distance(dust.begin(), it));

                if(dist[maskto][xto][yto] != -1)
                    continue;

                dist[maskto][xto][yto] = 1 + d;
                q.emplace(maskto, xto, yto);
            }
        }

        auto [xf, yf] = *finish;

        int answer {};
        bool is_reacheable {};

        for(int i = 0; i < (1 << n); ++i) {
            is_reacheable = is_reacheable || dist[i][xf][yf] != -1;
            answer = max(answer, dist[i][xf][yf] != -1 ? __builtin_popcount(i) : 0);
        }

        cout << (is_reacheable ? answer : -1) << '\n';
    }

    return 0;
}