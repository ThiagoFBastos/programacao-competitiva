#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e2 + 5, M = 1e3 + 5;

int mincost[N][M];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    using pq_type = tuple<int, size_t, size_t>;

    size_t n, m, q;

    cin >> n >> m;

    vector<vector<pair<size_t, int>>> adj(n);

    auto view = views::iota(size_t {}, n) | views::transform([](auto) { int x; cin >> x; return x;});

    vector<int> cost;

    ranges::copy(view, back_inserter(cost));

    for(size_t i = 0; i < m; ++i) {
        size_t u, v;
        int d;

        cin >> u >> v >> d;

        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }

    cin >> q;

    for(size_t i = 0; i < q; ++i) {
        size_t cap, s, t;

        cin >> cap >> s >> t;

        constexpr int INF = numeric_limits<int>::max();
        
        for(size_t c = 0; c <= cap; ++c)
            for(size_t u = 0; u < n; ++u)
                mincost[c][u] = INF;

        priority_queue<pq_type, vector<pq_type>, greater<pq_type>> pq;
        optional<int> answer;

        pq.emplace(0, 0, s);
        mincost[0][s] = 0;

        while(!pq.empty()) {
            auto [cst, fuel, u] = pq.top();

            pq.pop();

            if(mincost[fuel][u] != cst)
                continue;
            else if(u == t) {
                answer = cst;
                break;
            }

            if(int new_cost = cst + cost[u]; fuel < cap && new_cost < mincost[fuel + 1][u]) {
                mincost[fuel + 1][u] = new_cost;
                pq.emplace(new_cost, fuel + 1, u);
            }

            for(const auto& [v, d] : adj[u]) {
                if(d <= static_cast<int>(fuel) && cst < mincost[fuel - d][v]) {
                    mincost[fuel - d][v] = cst;
                    pq.emplace(cst, fuel - d, v);
                }
            }
        }

        if(answer) cout << *answer << '\n';
        else cout << "impossible\n";
    }

    return 0;
}