#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<size_t, int, int>;
using Adj = vector<vector<Edge>>;

vector<long long> dijkstra(const Adj& adj) {
    using pq_type = pair<long long, size_t>;

    const auto n = adj.size();
    constexpr auto INF = numeric_limits<long long>::max();
    
    vector<long long> dist(n, INF);
    priority_queue<pq_type, vector<pq_type>, greater<pq_type>> pq;

    pq.emplace(0LL, 0);
    dist[0] = 0;

    while(!pq.empty()) {
        auto [cost, u] = pq.top();

        pq.pop();

        if(dist[u] != cost)
            continue;

        for(auto [v, l, c] : adj[u]) {
            auto new_cost = cost + l;

            if(dist[v] <= new_cost)
                continue;

            dist[v] = new_cost;
            pq.emplace(new_cost, v);
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;

    cin >> n >> m;

    Adj adj(n);

    for(size_t i = 0; i < m; ++i) {
        size_t a, b;
        int l, c;

        cin >> a >> b >> l >> c;

        --a, --b;

        adj[a].emplace_back(b, l, c);
        adj[b].emplace_back(a, l, c);
    }

    auto cost = dijkstra(adj);

    vector<int> min_in_edge(n, INT_MAX);

    min_in_edge[0] = 0;

    for(size_t u = 0; u < n; ++u) {
        for(auto [v, l, c] : adj[u]) {
            if(cost[v] == cost[u] + l)
                min_in_edge[v] = min(min_in_edge[v], c);
        }
    }

    auto total_repair_cost = accumulate(min_in_edge.begin(), min_in_edge.end(), 0LL);

    cout << total_repair_cost << '\n';

    return 0;
}