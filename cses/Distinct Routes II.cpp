#include "bits/stdc++.h"
using namespace std;
 
using ii = pair<int, int>;
 
const int inf = 1e9;
 
struct Edge {
    int u, cap, flow {}, weight;
    Edge(int u, int cap, int weight) : u(u), cap(cap), weight(weight) {}
};
 
struct MCMF {
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> pi, dist;
    vector<ii> to;
    vector<bool> seen;
    int n, m = 0, s, t;
   
    MCMF(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        pi.resize(n);
        dist.resize(n);
        to.resize(n);
        seen.resize(n);
    }
 
    void add_edge(int v, int u, int cap, int weight) {
        edges.emplace_back(u, cap, weight);
        edges.emplace_back(v, 0, -weight);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
 
    void bellman_ford() {
        queue<int> q;
        vector<bool> in_queue(n, false);
        fill(pi.begin(), pi.end(), inf);
        q.push(s);
        pi[s] = 0;  
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            in_queue[v] = false;
            for(int e : adj[v]) {
                auto [u, cap, flow, weight] = edges[e];
                if(cap - flow <= 0) continue;
                int cost = pi[v] + weight;
                if(pi[u] > cost) {
                    pi[u] = cost;
                    if(!in_queue[u]) {
                        in_queue[u] = true;
                        q.push(u);
                    }
                }
            }
        }
    }
    
    void dijkstra() {
        priority_queue<ii> pq;
        pq.push({0, s});
        for(int v = 0; v < n; ++v) {
            seen[v] = false;
            dist[v] = inf;
        }
        dist[s] = 0;
        while(!pq.empty()) {
            auto [c, v] = pq.top();
            pq.pop();
            if(seen[v]) continue;
            seen[v] = true;
            for(int e : adj[v]) {
                auto [u, cap, flow, weight] = edges[e];
                int cost = dist[v] + weight + pi[v] - pi[u];
                if(cap - flow <= 0 || dist[u] <= cost) continue;
                dist[u] = cost;
                to[u] = {v, e};
                pq.push({-cost, u});    
            }
        }
    }
        
   auto min_cost_max_flow() {
      int cost, flow;
      cost = flow = 0;
      bellman_ford();
       for(;;) {
            dijkstra();
            
            if(dist[t] == inf) break;
     
            int f = inf;
            
            for(int v = t; v != s; v = to[v].first) {
                int e = to[v].second;
                f = min(f, edges[e].cap - edges[e].flow);
            }
            
            for(int v = t; v != s; v = to[v].first) {
                int e = to[v].second;
                edges[e].flow     += f;
                edges[e ^ 1].flow -= f;
            }
            
            cost += f * (dist[t] - pi[s] + pi[t]);
            flow += f;
 
            for(int i = 0; i < n; ++i) pi[i] += dist[i];
       }
        return make_pair(cost, flow);
    }
};
 
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    
    MCMF g(n + 1, 0, n);
 
    while(m--) {
        int a, b;
        cin >> a >> b;
        g.add_edge(a, b, 1, 1);
    }
 
    g.add_edge(0, 1, k, 0);
 
    auto [cost, flow] = g.min_cost_max_flow();
 
    if(flow < k) {
        cout << "-1\n";
        return;
    }
 
    cout << cost << '\n';
    
    vector<int> pos(n, 0);
 
    while(flow--) {
        vector<int> S{1};
        int v = 1;
        while(v != n) {
            for(int& i = pos[v]; i < int(g.adj[v].size()); ++i) {
                int e = g.adj[v][i];
                auto& [u, cap, flow, weight] = g.edges[e];
                if(!cap || flow != cap) continue;
                --flow;
                S.push_back(u);
                v = u;
                break;
            }
        }
        cout << S.size() << '\n';
        for(int x : S) cout << x << ' ';
        cout << '\n';
    }
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
