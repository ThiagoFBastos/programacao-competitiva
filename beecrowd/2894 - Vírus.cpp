#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t t;

    cin >> t;

    for(size_t i = 0; i < t; ++i) {
        size_t n, m, c;

        cin >> n >> m >> c;

        --c;

        vector<vector<pair<size_t, size_t>>> adj(n);
        vector<int> low(n), sz(n);
        vector<optional<int>> desc(n);
        vector<pair<size_t, size_t>> bridges;
        int timestamp {};

        for(size_t j = 0; j < m; ++j) {
            size_t u, v;

            cin >> u >> v;

            --u, --v;

            adj[u].emplace_back(v, j);
            adj[v].emplace_back(u, j);
        }

        auto dfs = [&](auto& self, size_t u, optional<pair<size_t, size_t>> parent) -> void {
            desc[u] = low[u] = timestamp++;
            sz[u] = 1;

            for(const auto& e : adj[u]) {
                const auto& [v, id] = e;

                if(!desc[v]) {
                    self(self, v, make_pair(u, id));
                    low[u] = min(low[u], low[v]);
                    sz[u] += sz[v];

                    if(*desc[u] < low[v])
                        bridges.emplace_back(u, v);
                } else if(e != parent)
                    low[u] = min(low[u], *desc[v]);
            }
        };

        dfs(dfs, c, nullopt);

        int max_number_of_cities {};

        for(const auto &[u, v] : bridges)
            max_number_of_cities = max(max_number_of_cities, sz[v]);

        cout << max_number_of_cities << '\n';
    }

    return 0;
}