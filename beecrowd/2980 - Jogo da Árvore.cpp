#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, x;
    int k;

    cin >> n;

    vector<vector<pair<int, int>>> adj(n);
    vector<optional<int>> dist(n);
    vector<long long> cost(n);
    queue<size_t> q;

    ranges::for_each(views::iota(size_t {1}, n), [&](auto) {
        size_t u, v;
        int w;

        cin >> u >> v >> w;

        --u, --v;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    });

    cin >> k >> x;

    q.emplace(--x);
    dist[x] = 0;
    cost[x] = 0;

    while(!q.empty()) {
        auto u = q.front();

        q.pop();

        if(*dist[u] == k)
            continue;

        for(const auto& [v, w] : adj[u]) {
            if(dist[v]) continue;
            dist[v] = 1 + *dist[u];
            cost[v] = w + cost[u];
            q.emplace(v);
        }
    }

    auto max_cost = numeric_limits<long long>::min();

    for(auto u : views::iota(size_t {}, n)) {

        if(!dist[u])
            continue;
            
        auto max_edge_weight = numeric_limits<long long>::min();

        for(const auto& [_, w] : adj[u])
            max_edge_weight = max<long long>(max_edge_weight, w);

        int d = *dist[u];
        auto cst = cost[u] + (k - d + 0ll) * max_edge_weight;

        max_cost = max(max_cost, cst);
    }

    cout << max_cost;

    return 0;
}