#include <bits/stdc++.h>

using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    while(true) {
        int n;

        cin >> n;

        if(n < 0)
            break;

        auto view = views::iota(1, n) | views::transform([](auto idx) {
            string schedule;
            cin >> schedule;
            return make_pair(idx, schedule);
        });

        vector<pair<int, string>> matches;

        ranges::copy(view, back_inserter(matches));

        auto index = [n](char i, char j) {
            if(i > j)
                swap(i, j);

            int x = i - '1';
            int y = j - '1';

            return x * n + y;
        };

        map<pair<int, int>, int> vertices;
        map<int, int> translator;
        vector<vector<int>> adj;

        auto add = [&](auto u, auto cnt) {
            auto t = make_pair(u, cnt);

            if(auto it = vertices.find(t); it != vertices.end())
                return it->second;

            adj.push_back({});
            translator[vertices.size()] = u;
            return vertices[t] = vertices.size();
        };

        for(const auto& [id, match]: matches) {
            int u = index(id + '1', match[0]);
            map<int, int> cnt;

            add(u, 1);
            cnt[u] = 1;

            for(size_t i = 1; i < match.size(); ++i) {
                int u = index(id + '1', match[i - 1]);
                int v = index(id + '1', match[i]);

                int x = vertices[{u, cnt[u]}];

                ++cnt[v];

                add(v, cnt[v]);

                int y = vertices[{v, cnt[v]}];

                adj[x].push_back(y);
            }
        }

        vector<int> toposort;
        vector<bool> vis(vertices.size(), false);
        string florencia_matches;

        function<void(int)> dfs = [&](int u) {
            vis[u] = true;

            for(const auto& v : adj[u]) {
                if(!vis[v])
                    dfs(v);
            }

            toposort.emplace_back(u);
        };

        ranges::for_each(views::iota(size_t {}, vertices.size()), [&](auto u) {
            if(!vis[u])
                dfs(u);
        });

        reverse(toposort.begin(), toposort.end());

        for(const auto& idx : toposort) {
            int p = translator[idx];
            int u = p / n;
            int v = p % n;

            if(u != 0 || u == v) continue;

            florencia_matches.push_back(v + '1');
        }

        cout << florencia_matches << '\n';
    };

    return 0;
}