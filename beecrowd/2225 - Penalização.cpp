#include <bits/stdc++.h>

using namespace std;

constexpr int N = 15, K = 6, INF = 1'000'000'000;

int adj[N][N], cost[(1 << N)][N][K];

struct pq_type {
    int v1, v2, v3, v4;

    pq_type() = default;

    pq_type(int a, int b, int c, int d):
        v1(a),
        v2(b),
        v3(c),
        v4(d)
    {}

    bool operator>(const pq_type& other) const {
        return v1 > other.v1;
    }

    bool operator<(const pq_type& other) const {
        return v1 < other.v1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t t;

    cin >> t;

    for(size_t i = 0; i < t; ++i) {
        size_t n, m, k;

        cin >> n >> m >> k;

        for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < n; ++j)
            adj[i][j] = INF;

        for(size_t i = 0; i < m; ++i) {
            size_t u, v;
            int c;

            cin >> u >> v >> c;

            --u, --v;

            adj[u][v] = min(adj[u][v], c);
            adj[v][u] = min(adj[v][u], c);
        }

        for(size_t i = 0; i < (size_t {1} << n); ++i)
            for(size_t src = 0; src < n; ++src)
                for(size_t j = 0; j <= k; ++j)
                    cost[i][src][j] = INF;

        priority_queue<pq_type, vector<pq_type>, greater<pq_type>> pq;
        optional<int> mincost;

        cost[1][0][0] = 0;
        pq.emplace(0, 1, 0, 0);

        while(!pq.empty()) {
            auto [cst, mask, src, j] = pq.top();

            pq.pop();

            if(cost[mask][src][j] != cst)
                continue;
            else if(mask == (1 << n) - 1) {
                mincost = cst;
                break;
            }

            for(size_t dest = 0; dest < n; ++dest) {
                auto dest_mask = mask | (1 << dest);
                auto dest_cost = cst + adj[src][dest];

                if(dest_cost < cost[dest_mask][dest][j]) {
                    cost[dest_mask][dest][j] = dest_cost;
                    pq.emplace(dest_cost, dest_mask, dest, j);
                }

                if(j < static_cast<int>(k) && cst < cost[dest_mask][dest][j + 1]) {
                    cost[dest_mask][dest][j + 1] = cst;
                    pq.emplace(cst, dest_mask, dest, j + 1);
                }
            }
        }

        if(mincost) cout << *mincost << '\n';
        else cout << "-1\n";
    }
    
    return 0;
}