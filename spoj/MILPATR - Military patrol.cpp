#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int inf = 1e9;
const i64 linf = 1e16L;

struct FlowEdge {
    int u; 
    i64 cap, flow {}, weight;
    FlowEdge(int u, i64 cap, i64 weight) : u(u), cap(cap), weight(weight) {}
};

struct mcmf {
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    vector<i64> pi, dist;
    vector<ii> to;
    vector<bool> seen;
    int n, m = 0, s, t;
   
    mcmf(int n, int s, int t) : n(n), s(s), t(t) {
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
        fill(pi.begin(), pi.end(), linf);
        q.push(s);
        pi[s] = 0;  
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            in_queue[v] = false;
            for(int e : adj[v]) {
                int u = edges[e].u;
                i64 cap = edges[e].cap, flow = edges[e].flow, weight = edges[e].weight;
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
            dist[v] = linf;
        }

        dist[s] = 0;
    
        while(!pq.empty()) {
            i64 c = pq.top().first;
            int v = pq.top().second;
           
            pq.pop();
            
            if(seen[v]) continue;
            
            seen[v] = true;

            for(int e : adj[v]) {
                int u = edges[e].u;
                i64 cap = edges[e].cap, flow = edges[e].flow, weight = edges[e].weight;
                i64 cost = dist[v] + weight + pi[v] - pi[u];
                if(cap - flow <= 0 || dist[u] <= cost) continue;
                dist[u] = cost;
                to[u] = {v, e};
                pq.push({-cost, u});    
            }
        }
    }
        
   void min_cost_max_flow(i64& cost, i64& flow) {
      cost = flow = 0;
     
      bellman_ford();
       
       for(;;) {
            dijkstra();
            
            if(dist[t] == linf) break;
     
            i64 f = linf;
            
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
    }
};

void solve() {
	int n, r;
	i64 a, b;

	cin >> n >> r;

	mcmf g(2 * n + 2, 2 * n, 2 * n + 1);
	
	while(r--) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		g.add_edge(2 * u, 2 * v + 1, 1, w);
	}

	for(int i = 0; i < n; ++i) {
		g.add_edge(2 * n, 2 * i, 1, 0);
		g.add_edge(2 * i + 1, 2 * n + 1, 1, 0);
	}

	g.min_cost_max_flow(a, b);

	if(b != n) cout << "Impossible\n";
	else cout << a << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}