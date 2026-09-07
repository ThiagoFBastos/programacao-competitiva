#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	
	while(cin >> n >> m) {
		vector<vector<int>> adj(n), keyLocation(n);

		for(int i = 0; i < m; ++i) {
			int u, v;
			cin >> u >> v;
			--u, --v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}

		for(int i = 1; i < n; ++i) {
			int loc;
			cin >> loc;
			keyLocation[loc - 1].push_back(i);
		}

		vector<bool> vis(n, false), border(n, false), keys(n, false);
		queue<int> q;

		/*
			1. vértice contém chave para outro vértice (não visitado) 
				1.1 - se está na borda
					- coloca esses vértices da fila
				1.2 - se não está na borda
					- guarda a chave
			2. vértice é adjacente a um vértice na borda não visitado
				- se já contém chave para ele coloca na fila
			3. resto dos vértices não visitados
				- coloca na borda 
		*/

		vis[0] = true;
		q.push(0);

		while(!q.empty()) {
			int u = q.front();

			q.pop();

			for(int v : keyLocation[u]) {
				keys[v] = true;

				if(!vis[v] && border[v]) {
					vis[v] = true;
					q.push(v);
				}
			}

			for(int v : adj[u]) {
				if(vis[v])
					continue;
				else if(keys[v]) {
					vis[v] = true;
					q.push(v);
				} else
					border[v] = true;
			}
		}

		if(ranges::all_of(vis, identity()))
			cout << "sim\n";
		else
			cout << "nao\n";
	}

	return 0;
}