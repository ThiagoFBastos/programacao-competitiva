#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m, instance {};

    while(cin >> n >> m && (n > 0 || m > 0)) {
        vector<vector<pair<int, int>>> adj(n);
        vector<int> heights;

        heights.reserve(m);

        for(size_t i = 0; i < m; ++i) {
            int u, v, h;

            cin >> u >> v >> h;

            --u, --v;

            adj[u].emplace_back(v, h);
            adj[v].emplace_back(u, h);
            heights.emplace_back(h);
        }

        sort(heights.begin(), heights.end());
        heights.resize(unique(heights.begin(), heights.end()) - heights.begin());

        auto min_height_path = [&](int src, int dest, int threshold) {
            vector<bool> vis(n, false);
            queue<int> q;

            vis[src] = true;
            q.push(src);

            while(!q.empty()) {
                int u = q.front();

                q.pop();

                if(u == dest)
                    break;

                for(const auto& [v, h] : adj[u]) {
                    if(h > threshold || vis[v]) continue;
                    vis[v] = true;
                    q.push(v);
                }
            }

            return static_cast<bool>(vis[dest]);
        };

        auto query = [&](int u, int v) {
            size_t lo = 0, hi = heights.size() - 1;

            while(lo < hi) {
                auto mid = (lo + hi) / 2;

                if(min_height_path(u, v, heights[mid]))
                    hi = mid;
                else
                    lo = mid + 1;
            }

            return heights[hi];
        };
        
        size_t q;

        cin >> q;

        cout << "Instancia " << ++instance << '\n';

        for(size_t i = 0; i < q; ++i) {
            int u, v;

            cin >> u >> v;

            --u, --v;

            if(u == v) {
                cout << "0\n";
                continue;
            }

            cout << query(u, v) << '\n';
        }

        cout << '\n';
    }

    return 0;
}