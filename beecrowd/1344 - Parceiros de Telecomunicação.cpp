#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, p, k;

    while(cin >> n >> p >> k && n) {
        vector<set<int>> adj(n);
        queue<int> q;

        for(size_t i = 0; i < p; ++i) {
            int u, v;

            cin >> u >> v;
            --u, --v;
            
            adj[u].emplace(v);
            adj[v].emplace(u);
        }
        
        for(size_t u = 0; u < n; ++u) {
            if(adj[u].size() < k)
                q.push(u);
        }
        
        while(!q.empty()) {
            int u = q.front();

            q.pop();

            for(const auto& v : adj[u]) {

                auto deg = adj[v].size();

                adj[v].erase(u);

                if(deg == k && adj[v].size() < k)
                    q.push(v);
            }

            adj[u].clear();
        }

        int largest_subset {};
        vector<bool> vis(n, false);
        
        for(size_t u = 0; u < n; ++u) {
            if(vis[u] || adj[u].size() < k) continue;

            queue<int> q;
            int cnt {};

            vis[u] = true;
            q.push(u);

            while(!q.empty()) {
                int u = q.front();

                q.pop();

                ++cnt;

                for(const auto& v : adj[u]) {
                    if(vis[v]) continue;
                    vis[v] = true;
                    q.push(v);
                }
            }

            largest_subset = max(largest_subset, cnt);
        }
        
        cout << largest_subset << '\n';
    }

    return 0;
}