#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

static vi *G, w;
static int k = 0;

static void dfs(int);

void dfs(int v) {

	w[v] = k;
	
	for(int u : G[v]) {
	
		if(w[u] == -1)
			dfs(u);
	}
}


static int query(int*, int);

static void update(int*, int, int);

int query(int *bit, int r) {

	int sum {};
	
	while(r > 0) {
	
		sum += bit[r];
		r -= r & -r;
	}
	
	return sum;
}

void update(int *bit, int i, int x) {
	
	while(i <= 100) {
	
		bit[i] += x;
		i += i & -i; 
	}
}

int main() {
	
	int n, m, **bit;
	
	scanf("%d", &n);
		
	vi notas(n);
	
	for(int i = 0; i < n; ++i) scanf("%d", &notas[i]);
	
	G = new vi[n];
	
	scanf("%d", &m);
	
	for(int i = 0; i < m; ++i) {
	
		int u, v;
		
		scanf("%d%d", &u, &v);
		
		--u;
		--v;
		
		G[u].push_back(v);
		G[v].push_back(u);
	}
	
	w.assign(n, -1);
	
	for(int i = 0; i < n; ++i) {
	
		if(w[i] == -1) {
		
			dfs(i);
			++k;
		}
	}
	
	bit = new int*[k];
	
	for(int i = 0; i < k; ++i) {
	
		bit[i] = new int[101];
		memset(bit[i], 0, sizeof(int) * 101);
	}
	
	for(int i = 0; i < n; ++i)
		update(bit[w[i]], notas[i], 1);
	
	int q;
	
	scanf("%d", &q);
		
	for(int i = 0; i < q; ++i) {
	
		int t, a;
		
		scanf("%d%d", &t, &a);
		
		--a;
		
		if(t == 1)
			printf("%d\n", query(bit[w[a]], notas[a] - 1));
		
		else {
		
			int b;
			
			scanf("%d", &b);
			
			update(bit[w[a]], notas[a], -1);
			
			notas[a] = b;
			
			update(bit[w[a]], notas[a], 1);
		}
	}
	
	return 0;
}