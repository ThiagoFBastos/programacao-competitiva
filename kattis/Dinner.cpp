#include "bits/stdc++.h"
using namespace std;
const int MAXN = 400;
int y[MAXN][MAXN], g[MAXN][MAXN];
void solve() {
    int n, m;
    cin >> n >> m;
    for(int u = 0; u < n; ++u)
    for(int v = 0; v < n; ++v)
        y[u][v] = u != v ? 2008 : 0;
    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        y[a][b] = y[b][a] = c; 
    }
    vector<int> deg(n);
    vector<bool> visto(n);
    for(int ano = 1948; ano <= 2008; ++ano) {
        set<pair<int, int>> S;
        bool ok = true;
        int X = 0, Y = 0;
        for(int u = 0; u < n; ++u) {
            deg[u] = 0;
            visto[u] = false;
            for(int v = 0; v < n; ++v) {
                g[u][v] = y[u][v] >= ano;
                deg[u] += g[u][v];
            }
            S.insert({deg[u], u});
        }
        while(!S.empty()) {
            auto [d, u] = *S.begin();
            if(d == size(S) - 1) break;
            S.erase(S.begin());
            for(int v = 0; v < n; ++v) {
                if(!g[u][v]) continue;
                g[u][v] = g[v][u] = 0;
                S.erase({deg[v], v});
                --deg[v];
                S.insert({deg[v], v});
            }
        }
        X = size(S);
        Y = n - X;
        while(!S.empty()) {
            auto [d, u] = *S.begin();
            S.erase(S.begin());
            visto[u] = true;
        }
        for(int u = 0; u < n; ++u) {
            if(visto[u]) continue;
            for(int v = 0; v < n; ++v) {
                if(visto[v]) continue;
                else if(y[u][v] >= ano) ok = false;
            }
        }
        if(!ok) continue;
        if(X > 2 * n / 3) {
            for(int u = 0; u < n; ++u) {
                bool flag = true;
                if(!visto[u]) continue;
                for(int v = 0; v < n; ++v) {
                    if(visto[v]) continue;
                    else if(y[u][v] >= ano) flag = false;
                }
                if(flag) {
                    --X, ++Y;
                    break;
                }
            }
        }
        if(max(X, Y) > 2 * n / 3) continue;
        cout << ano << '\n';
        return;
    }
    cout << "Impossible\n";
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
