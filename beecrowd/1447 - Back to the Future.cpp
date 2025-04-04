#include "bits/stdc++.h"
using namespace std;

using ll = long long;

using ii = pair<int, int>;
using T = pair<ll, int>;

const int inf = 1e9;
const ll linf = 1e15L + 100;

struct FlowEdge {
    int u;
    ll cap, flow {}, weight;
    FlowEdge(int u, ll cap, ll weight) : u(u), cap(cap), weight(weight) {}
};

struct MCMF {
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    vector<ll> pi, dist;
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

    void add_edge(int v, int u, ll cap, ll weight) {
        edges.emplace_back(u, cap, weight);
        edges.emplace_back(v, 0, -weight);
        edges.emplace_back(v, cap, weight);
        edges.emplace_back(u, 0, -weight);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        adj[u].push_back(m + 2);
        adj[v].push_back(m + 3);
        m += 4;
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
    	priority_queue<T> pq;
    	pq.push({0, s});
    	fill(seen.begin(), seen.end(), false);
    	fill(dist.begin(), dist.end(), linf);
    	dist[s] = 0;
    	while(!pq.empty()) {
    		auto [c, v] = pq.top();
    		pq.pop();
    		c *= -1;
    		if(seen[v]) continue;
    		else if(v == t) break;
    		seen[v] = true;
			for(int e : adj[v]) {
				auto [u, cap, flow, weight] = edges[e];
    			if(cap - flow <= 0 || dist[u] <= dist[v] + weight + pi[v] - pi[u]) continue;
    			dist[u] = dist[v] + weight + pi[v] - pi[u];
    			to[u] = {v, e};
    			pq.push({-dist[u], u});	
			}
    	}
    }
    	
   auto minCostmaxFlow() {
   	 ll cost = 0, flow = 0;
   	 
      bellman_ford();
       
       for(;;) {
       		dijkstra();
       		
       		if(dist[t] == linf) break;
     
       		auto f = linf;
       		
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

int caso;

void solve() {
	int n, m;
	ll d, k;
	cin >> n >> m;
	if(cin.eof()) exit(0);
	
	MCMF G(n + 1, 0, n);
	vector<tuple<int, int, ll>> edges(m);
	
	for(int i = 0; i < m; ++i) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		edges[i]= {a, b, c};
	}
	
	cin >> d >> k;
	
	for(auto [a, b, c] : edges) G.add_edge(a, b, k, c);
	
	G.add_edge(0, 1, d, 0);
	
	auto [cost, flow] = G.minCostmaxFlow();
	
	cout << "Instancia " << ++caso << '\n';
	if(flow < d) cout << "impossivel";
	else cout << cost;
	cout << "\n\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(true) solve();
 	return 0;
}