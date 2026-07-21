#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;

    cin >> t;

    auto is_dag = [](const auto& adj) {
        const auto n = adj.size();
        vector<int> in(n, 0);
        queue<size_t> q;

        for(size_t u = 0; u < n; ++u)
            for(auto v : adj[u])
                ++in[v];

        for(size_t u = 0; u < n; ++u) {
            if(!in[u])
                q.push(u);
        }

        size_t reachable {};

        while(!q.empty()) {
            auto u = q.front();

            q.pop();

            ++reachable;

            for(auto v : adj[u]) {
                if(--in[v] == 0)
                    q.push(v);
            }
        }

        return reachable == n;
    };

    while(t-- > 0) {
        int n, m;

        cin >> n >> m;

        vector<vector<size_t>> adj(n);

        for(int i = 0; i < m; ++i) {
            size_t a, b;
            cin >> a >> b;
            --a, --b;
            adj[a].push_back(b);
        }

        if(is_dag(adj))
            cout << "NAO\n";
        else
            cout << "SIM\n";
    }

    return 0;
}