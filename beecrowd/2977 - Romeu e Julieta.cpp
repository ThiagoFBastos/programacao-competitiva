#include <bits/stdc++.h>

using namespace std;

using result_type = std::optional<int>;
using adjacency_list = std::vector<std::vector<std::pair<int, int>>>;

std::vector<result_type> dijkstra(const adjacency_list& adj, std::size_t start)
{
    using pq_type = std::pair<int, int>;

    const auto n = adj.size();

    std::vector<result_type> dist(n);
    std::priority_queue<pq_type, std::vector<pq_type>, std::greater<pq_type>> pq;

    pq.emplace(0LL, start);

    while(!pq.empty())
    {
        auto [cost, start] = pq.top();

        pq.pop();

        if(dist[start].has_value())
            continue;

        dist[start] = cost;

        for(const auto& [dest, weight] : adj[start])
        {
            if(dist[dest].has_value())
                continue;

            pq.emplace(cost + weight, dest);
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t n, m;
    size_t js, jg, rs, rg;

    cin >> n >> m;
    cin >> js >> jg >> rs >> rg;

    --js, --jg, --rs, --rg;

    adjacency_list adj(n), inv_adj(n);

    for(size_t i = 0; i < m; ++i) {
        size_t u, v;
        int t;

        cin >> u >> v >> t;

        --u, --v;
        adj[u].emplace_back(v, t);
        inv_adj[v].emplace_back(u, t);
    }
    
    auto jto = dijkstra(adj, js);
    auto jfrom = dijkstra(inv_adj, jg);
    auto rto = dijkstra(adj, rs);
    auto rfrom = dijkstra(inv_adj, rg);

    optional<int> meeting;

    for(size_t u = 0; u < n; ++u) {
        if(!jto[u] || !jfrom[u] || *jto[u] + *jfrom[u] != *jto[jg] || *rto[u] + *rfrom[u] != *rto[rg] || *jto[u] != *rto[u])
            continue;

        meeting = min(meeting.value_or(numeric_limits<typename decltype(meeting)::value_type>::max()), *jto[u]);
    }

    if(meeting)
        cout << *meeting << '\n';
    else
        cout << "-1\n";

    return 0;
}