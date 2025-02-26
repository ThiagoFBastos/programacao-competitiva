#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("mmx","sse","sse2","avx")

#include "bits/stdc++.h"

using namespace std;

const int N = 5e5 + 1;
const long long INF = 1e12L;

long long max_weight[N];
vector<int> g[N], label, sz;
int n, fat[N];
vector<long long> weight;
vector<vector<pair<int, int>>> G;
vector<bool> vis;

int get(int u, int p = -1) {
    sz[u] = 1;
    for(int x : g[label[u]]) max_weight[x] = -INF;
    for(auto [v, w] : G[u]) {
        if(v == p || vis[v]) continue;
        get(v, u);
        sz[u] += sz[v];
    }
    if(p != -1) return -1;
    int n = sz[u];
    while(true) {
        auto x = make_pair(n - sz[u], u);
        for(auto [v, w] : G[u]) {
            if(v == p || vis[v]) continue;
            x = max(x, make_pair(sz[v], v));
        }
        if(x.first <= n / 2) break;
        p = u, u = x.second;
    }
    return u;
}

auto ans = 0LL;
vector<pair<int, long long>> E;

void dfs(int u, int p = -1) {
    if(p == -1) {
        weight[u] = 0;
        for(int x : g[label[u]]) max_weight[x] = 0;
    } else {
        for(int x : g[label[u]]) {
            ans = max(ans, x * (weight[u] + max_weight[x]));
            E.push_back({x, weight[u]});
        }
    }
    for(auto [v, w] : G[u]) {
        if(v == p || vis[v]) continue;
        weight[v] = w + weight[u];
        dfs(v, u);
        if(p == -1) {
            for(auto [x, y] : E) max_weight[x] = max(max_weight[x], y);
            E.clear();
        }
    }
}


void centroid(int u) {
    u = get(u);
    vis[u] = true;
    dfs(u);
    for(auto [v, w] : G[u]) {
        if(vis[v]) continue;
        centroid(v);
    }
}

void solve() {
    cin >> n;
    if(!n) exit(0);
    G.clear();
    G.resize(n);
    weight.resize(n);
    label.resize(n);
    sz.resize(n);
    vis.assign(n, false);
    for(int i = 0; i < n; ++i) cin >> label[i];
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    ans = 0;
    centroid(0);
    cout << ans << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    for(int k = 2; k * k < N; ++k) {
        if(fat[k]) continue;
        for(int i = k; i < N; i += k) fat[i] = k;
    }
    g[1] = {1};
    for(int k = 2; k < N; ++k) {
        if(!fat[k]) fat[k] = k;
        int i = k, cnt = 0, x = 1;
        while(fat[i] == fat[k]) {
            i /= fat[k];
            ++cnt;
        }
        g[k] = g[i];
        while(cnt--) {
            x *= fat[k];
            for(int j = 0; j < int(size(g[i])); ++j) g[k].push_back(g[i][j] * x);
        }
    }
    for(;;) solve();
    return 0;
}