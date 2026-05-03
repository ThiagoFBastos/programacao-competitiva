#include <bits/stdc++.h>

using namespace std;

int bfs(const vector<vector<int>>& adj, int origem, int destino) {
    const auto n = adj.size();
    queue<int> q;
    vector<int> dist(n, -1);

    q.push(origem);
    dist[origem] = 0;

    while(!q.empty()) {
        int v = q.front();

        q.pop();

        for(int u : adj[v]) {
            if(dist[u] != -1)
                continue;

            dist[u] = 1 + dist[v];
            q.push(u);
        }
    }

    return dist[destino];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int pontos, ligacoes;
    unordered_map<string, int> identificador;

    cin >> pontos >> ligacoes;

    identificador.reserve(pontos);

    vector<vector<int>> adj(pontos);

    auto index = [&](const string& nome) {
        if(auto it = identificador.find(nome); it != identificador.end())
            return it->second;

        return identificador[nome] = identificador.size();
    };

    for(int i = 0; i < ligacoes; ++i) {
        string p1, p2;

        cin >> p1 >> p2;

        adj[index(p1)].push_back(index(p2));
        adj[index(p2)].push_back(index(p1));
    }

    int distancia = bfs(adj, index("Entrada"), index("*")) + bfs(adj, index("*"), index("Saida"));

    cout << distancia << '\n';

    return 0;
}