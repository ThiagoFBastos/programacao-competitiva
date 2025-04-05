#include <bits/stdc++.h>

static int *rank, *parent;

static void link(int, int);
static int find_set(int);

void link(int u, int v) {

	if(rank[u] < rank[v])
		parent[u] = v;
		
	else {
	
		parent[v] = u;
		
		if(rank[u] == rank[v]) ++rank[u];
	}
}

int find_set(int v) {

	return v == parent[v] ? v : parent[v] = find_set(parent[v]);
}

using ii = std :: pair<int, int>;
using vi = std :: vector<ii>;

static vi *T;
static int *altura, **st, **mincost, K;

static void dfs(int);
static int lca(int, int);
static int min_cost(int, int);

void dfs(int v) {

	for(auto [u, custo] : T[v]) {
	
		if(altura[u] == -1) {
		
			altura[u] = 1 + altura[v];
			
			mincost[u][0] = custo;
			st[u][0] = v;
			
			dfs(u);
		}
	}
}

int lca(int u, int v) {

	if(altura[u] > altura[v]) u ^= v ^= u ^= v;
	
	int LV = altura[v];
	
	for(int i = K; i >= 0; --i) {
	
		if(LV - (1 << i) >= altura[u]) {
		
			LV -= 1 << i;
			v = st[v][i];
		}
	}
	
	if(u == v) return u;
	
	for(int i = K; i >= 0; --i) {
	
		if(st[u][i] != st[v][i]) {
		
			u = st[u][i];
			v = st[v][i];
		}
	}
	
	return st[u][0];
}

int min_cost(int u, int v) {
	
	int LCA = lca(u, v);
		 
	int X {}, Y {}, H = altura[u] - altura[LCA];
	
	for(int i = K; i >= 0; --i) {
	
		if(H >= 1 << i) {
		
			H -= 1 << i;
			X = std :: max(X, mincost[u][i]);
			u = st[u][i];
		}
	}
	
	H = altura[v] - altura[LCA];
	
	for(int i = K; i >= 0; --i) {
	
		if(H >= 1 << i) {
		
			H -= 1 << i;
			Y = std :: max(Y, mincost[v][i]);
			v = st[v][i];
		}
	}
	
	return std :: max(X, Y);
}

int main() {

	int n, m;
	std :: vector<std :: tuple<int, int, int>> arestas;
	
	scanf("%d%d", &n, &m);
	
	T = new vi[n];
	altura = new int[n];
	st = new int*[n];
	mincost = new int*[n];
	rank = new int[n];
	parent = new int[n];
	
	K = log2(n);
	
	for(int i = 0; i < n; ++i) {
	
		altura[i] = -1;
		rank[i] = 0;
		parent[i] = i;
		
		st[i] = new int[K + 1];
		mincost[i] = new int[K + 1];
	}
	
	arestas.resize(m);
	
	for(int i = 0; i < m; ++i) {
	
		int u, v, custo;
		
		scanf("%d%d%d", &u, &v, &custo);
		
		arestas[i] = std :: make_tuple(u, v, custo);
	}
	
	std :: sort(arestas.begin(), arestas.end(), [](std :: tuple<int, int, int> e, std :: tuple<int, int, int> d) {
	
		return std :: get<2>(e) < std :: get<2>(d);
	}); 
	
	for(auto [u, v, custo] : arestas) {
	
		int x, y;
		
		x = find_set(u);
		y = find_set(v);
		
		if(x != y) {
	
			link(x, y);
			
			T[u].push_back({v, custo});
			T[v].push_back({u, custo});
		}
	}
	
	altura[0] = 0;
	st[0][0] = 0;
	mincost[0][0] = 0;
	
	dfs(0);
	
	for(int i = 1; i <= K; ++i) {
	
		for(int j = 0; j < n; ++j) {
	
			st[j][i] = st[st[j][i - 1]][i - 1];
			mincost[j][i] = std :: max(mincost[j][i - 1], mincost[st[j][i - 1]][i - 1]);
		}
	}
			
	int queries;
	
	scanf("%d", &queries);
	
	for(int i = 0; i < queries; ++i) {
	
		int src, dest;
		
		scanf("%d%d", &src, &dest);
		
		printf("%d\n", min_cost(src, dest));
	}
	
	return 0;
	
}