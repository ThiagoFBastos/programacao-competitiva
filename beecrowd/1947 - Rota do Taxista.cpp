#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e4 + 5, K = 15, INF = 1e9;

vector<pair<int, int>> adj[N];
int dp[1 << K][K], pairwiseDist[K + 1][K + 1]; 
int n, m, k;

vector<int> dijkstra(int src) {
    using pq_type = pair<int, int>;

    vector<int> dist(n, INF);
    priority_queue<pq_type, vector<pq_type>, greater<pq_type>> pq;

    dist[src] = 0;
    pq.emplace(0, src);

    while(!pq.empty()) {
        auto [cost, v] = pq.top();

        pq.pop();

        if(cost != dist[v]) {
            continue;
        }

        for(const auto& [u, w] : adj[v]) {
            int total_cost = cost + w;

            if(dist[u] > total_cost) {
                dist[u] = total_cost;
                pq.emplace(total_cost, u);
            }
        }
    }

    return dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    
    for(int i = 0; i < m; ++i) {
        int u, v, w;

        cin >> u >> v >> w;

        --u, --v;

        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    vector<pair<int, int>> travels(k + 1);

    for(int i = 0; i < k; ++i) {
        int src, dest;

        cin >> src >> dest;

        travels[i] = {src - 1, dest - 1};
    }

    travels[k] = {0, 0};

    for(int i = 0; i <= k; ++i) {
        auto [src1, dest1] = travels[i];

        pairwiseDist[i][i] = dijkstra(src1)[dest1];

        auto costs = dijkstra(dest1);

        for(int j = 0; j <= k; ++j) {
            if(i == j)
                continue;

            int src2 = travels[j].first;

            pairwiseDist[i][j] = costs[src2];
        }
    }

    for(int i = 0; i < (1 << k); ++i)
        for(int j = 0; j < k; ++j)
            dp[i][j] = INF;

    for(int i = 0; i < k; ++i)
        dp[1 << i][i] = pairwiseDist[k][i] + pairwiseDist[i][i];

    for(int i = 0; i < (1 << k); ++i) {
        for(int j = i; j; j -= j & -j) {
            int u = __builtin_ctz(j);

            for(int l = i; l; l -= l & -l) {
                int v = __builtin_ctz(l);

                dp[i][v] = min(dp[i][v], dp[i ^ (1 << v)][u] + pairwiseDist[u][v] + pairwiseDist[v][v]);
            }
        }
    }

    int min_travel_cost {INF};

    for(int i = 0; i < k; ++i)
        min_travel_cost = min(min_travel_cost, dp[(1 << k) - 1][i] + pairwiseDist[i][k]);

    cout << min_travel_cost << '\n';

    return 0;
}