#include <bits/stdc++.h>

using namespace std;

struct FlowEdge {
    int v, u;
	long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

class Dinic {
public:
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].emplace_back(m);
        adj[u].emplace_back(m + 1);
        m += 2;
    }

    bool bfs() {
    	std::fill(level.begin(), level.end(), -1);    
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for(int id : adj[v]) {
                if(edges[id].cap - edges[id].flow < 1 || level[edges[id].u] != -1) continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if(!pushed || v == t) return pushed;
        for(int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if(level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
            long long tr = dfs(u, std::min(pushed, edges[id].cap - edges[id].flow));
            if(tr == 0) continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
    
   long long flow() {
        constexpr long long inf = 1e16L;
        long long f = 0;
        
        while(bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while(long long pushed = dfs(s, inf)) f += pushed;
        }
        return f;
    }

private:
    std::vector<FlowEdge> edges;
    std::vector<std::vector<int>> adj;
    int n, m = 0, s, t;
    std::vector<int> level, ptr;
    std::queue<int> q;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t t;

    cin >> t;

    for(size_t i = 0; i < t; ++i) {
        size_t n, m;

        cin >> n >> m;

        map<pair<size_t, size_t>, int> graph;

        for(size_t j = 0; j < m; ++j) {
            size_t u, v;
            int c;

            cin >> u >> v >> c;

            if(u > v) swap(u, v);

            graph[{u, v}] = c;
        }

        auto view = graph | views::transform([](auto& edge) {
            auto [e, c] = edge;
            auto [u, v] = e;
            return make_tuple(u, v, c);
        });

        vector<tuple<size_t, size_t, int>> edges;

        ranges::copy(view, back_inserter(edges));

        constexpr auto INF = static_cast<long long>(1e18L);
        auto mincost = numeric_limits<long long>::max();

        for(size_t j = 1; j < n; ++j) {
            Dinic din(n + 2, n, n + 1);

            din.add_edge(n, 0, INF);
            din.add_edge(j, n + 1, INF);

            for(const auto& [u, v, c] : edges) {
                din.add_edge(u, v, c);
                din.add_edge(v, u, c);
            }

            auto flow = din.flow();

            mincost = min(mincost, flow);
        }

        cout << mincost << '\n';
    }
    
    return 0;
}