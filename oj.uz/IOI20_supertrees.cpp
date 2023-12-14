#include "supertrees.h"
#include <bits/stdc++.h>
 
using namespace std;
 
struct DSU {
	vector<int> pai, rank, sz;
	
	DSU(int n) {
		pai.resize(n);
		rank.assign(n, 0);
		sz.assign(n, 1);
		iota(pai.begin(), pai.end(), 0);
	}
	
	int findSet(int v) {
		return v == pai[v] ? v : pai[v] = findSet(pai[v]);
	}
	
	int join(int a, int b) {
		a = findSet(a);
		b = findSet(b);
		if(a == b) return 0;
		else if(rank[a] > rank[b]) swap(a, b);
		pai[a] = b;
		rank[b] += rank[a] == rank[b];
		sz[b] += sz[a];
		return 1;
	}
};
 
int construct(vector<vector<int>> p) {
	int n = p.size();
	
	for(int u = 0; u < n; ++u) {
		for(int v = 0; v < n; ++v) {
			if(p[u][v] == 3)
				return 0;
		}
	}
	
	vector<int> id(n, -1);
	auto g = vector<vector<int>>(n, vector<int>(n, 0));
	DSU dsu(n), w(n);
	
	int t = 0;
	
	for(int v = 0; v < n; ++v) {
		if(id[v] != -1) continue;
		
		queue<int> q;
		vector<int> comp;
		
		id[v] = t;
		q.push(v);
		
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			
			comp.push_back(u);
			
			for(int v = 0; v < n; ++v) {
			
				if(p[u][v] == 1) dsu.join(u, v);
				
				if(id[v] != -1 || p[u][v] == 0) continue;
				
				id[v] = t;
				q.push(v);
			}
		}
		
		for(int i = 0; i < (int)comp.size(); ++i) {
			int u = comp[i];
			for(int j = i + 1; j < (int)comp.size(); ++j) {
				int v = comp[j];
		
				int U = dsu.findSet(u);
				int V = dsu.findSet(v);
					
				if(U == V && p[u][v] != 1 || U != V && p[u][v] != 2) return 0;
			}
		}
		
		for(int i = 0; i < (int)comp.size(); ++i) {
			int u = comp[i];
			for(int j = i + 1; j < (int)comp.size(); ++j) {
				int v = comp[j];
				
				int U = dsu.findSet(u);
				int V = dsu.findSet(v);
				
				if(U == V) g[u][v] = g[v][u] = w.join(u, v);
			}
		}
		
		vector<int> cycle;
		
		for(int v : comp) if(dsu.findSet(v) == v) cycle.push_back(v);
		
		if((int)cycle.size() == 2) return 0;
		
		if((int)cycle.size() > 1) {
			for(int i = 0; i < (int)cycle.size(); ++i) {
				int u = cycle[i];
				int v = cycle[(i + 1) % cycle.size()];
				g[u][v] = g[v][u] = 1;
			}
		}
			
		++t;
	}
	
	build(g);
	
	return 1;
}
