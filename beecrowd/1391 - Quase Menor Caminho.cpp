#include <bits/stdc++.h>

using namespace std;

using element = pair<int, int>;

vector<int> dijkstra(const vector<vector<element>>& adj, int origem, int destino) {
    const auto n = adj.size();
    priority_queue<element, vector<element>, greater<element>> pq;
    vector<int> custo(n, -1);

    pq.emplace(0, origem);

    while(!pq.empty()) {
        auto [c, v] = pq.top();

        pq.pop();

        if(custo[v] != -1)
            continue;

        custo[v] = c;

        for(auto [u, w] : adj[v]) {
            if(custo[u] == -1)
                pq.emplace(w + c, u);
        }
    }

    return custo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, m;

    while(cin >> n >> m && n && m) {
        int origem, destino;

        vector<vector<element>> adj(n), inv_adj(n);

        cin >> origem >> destino;

        for(int i = 0; i < m; ++i) {
            int u, v, custo;

            cin >> u >> v >> custo;

            adj[u].emplace_back(v, custo);
            inv_adj[v].emplace_back(u, custo);
        }

        auto da_origem = dijkstra(adj, origem, destino);
        auto do_destino = dijkstra(inv_adj, destino, origem);

        auto menor_caminho = da_origem[destino];

        auto remove_min_path_edges = [&]() {
            for(int u = 0; u < n; ++u) {
                int tamanho = 0;

                for(auto [v, w] : adj[u]) {
                    if(da_origem[u] + w + do_destino[v] != menor_caminho)
                        adj[u][tamanho++] = {v, w};
                }

                adj[u].resize(tamanho);
            }
        };

        remove_min_path_edges();

        auto da_origem_sem_menor_caminho = dijkstra(adj, origem, destino);

        cout << da_origem_sem_menor_caminho[destino] << '\n';
    }

    return 0;
}