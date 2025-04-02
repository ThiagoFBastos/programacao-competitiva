#include "bits/stdc++.h"
using namespace std;
using ii = tuple<int, int, int>;
vector<ii> diam(vector<vector<int>>& G) {
    int n = size(G), id = 0;
    vector<int> t(n), deg(n), W(n, -1);
    queue<int> q;
    for(int v = 0; v < n; ++v) {
        deg[v] = size(G[v]);
        if(deg[v] <= 1) {
            t[v] = 0;
            q.push(v);
        }
        if(W[v] != -1) continue;
        queue<int> q;
        q.push(v);
        W[v] = id;
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(int u : G[v]) {
                if(W[u] != -1) continue;
                W[u] = id;
                q.push(u);
            }
        }
        ++id;
    }
    vector<ii> c(id, make_tuple(-1, -1, -1));
    vector<int> cnt(id, 0);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        c[W[v]] = max(c[W[v]], make_tuple(t[v], t[v], v));
        for(int u : G[v]) {
            if(--deg[u] == 1) {
                t[u] = 1 + t[v];
                q.push(u);
            }
        }
    }
    for(int v = 0; v < n; ++v) if(get<0>(c[W[v]]) == t[v]) ++cnt[W[v]];
    for(int v = 0; v < id; ++v) {
        get<1>(c[v]) = 2 * get<0>(c[v]) + cnt[v] - 1;
        get<0>(c[v]) += cnt[v] - 1;
    }
    return c;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n);
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    auto C = diam(G);
    sort(C.rbegin(), C.rend());
    for(int i = 1; i < int(C.size()); ++i) {
        int x = get<2>(C[0]), y = get<2>(C[i]);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    C = diam(G);
    sort(C.rbegin(), C.rend());
    cout << get<1>(C[0]) << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}