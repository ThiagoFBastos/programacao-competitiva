#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

int n;
vector<vector<ii>> g;
vector<int> pre;

void dfs(int u, int p) {
    for(auto [v, w] : g[u]) {
        if(v == p) continue;
        pre[v] = pre[u] ^ w;
        dfs(v, u);
    }
}

struct DSU {
    vector<int> pai;
    vector<map<int, int>> dsu;
    
    DSU(int n) {
        pai.resize(n);
        dsu.resize(n);
        for(int i = 0; i < n; ++i) {
            pai[i] = i;
            dsu[i][0] = 1;
        }
    }
    
    int findSet(int v) {
        return v == pai[v] ? v : pai[v] = findSet(pai[v]);
    }
    
    i64 join(int a, int b, int c) {
        i64 pairs = 0;
        
        if(dsu[a].size() > dsu[b].size()) swap(a, b);
        
        pai[a] = b;
        
        for(auto [x, y] : dsu[a]) {
            auto k = dsu[b].find(x ^ c);
            if(k != dsu[b].end()) pairs += (i64)k->second * y;
        }
        
        for(auto [x, y] : dsu[a]) dsu[b][x ^ c] += y;
        
        return pairs;
    }
};

void solve() {
    
    cin >> n;
    
    if(n == 1) {
        cout << "0\n";
        return;
    }
    
    g.resize(n);
    pre.assign(n, 0);
    
    vector<tuple<int, int, int>> edges(n - 1);
    vector<bool> marked(n - 1, false);
    vector<int> p(n - 1);
    DSU dsu(n);
    vector<i64> pairs(n, 0);
    
    for(int i = 1; i < n; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
        edges[i - 1] = {a, b, c};
    }
    
    dfs(0, 0);
    
    for(int i = 0; i < n - 1; ++i) {
        cin >> p[i];
        marked[--p[i]] = true;
    }
    
    for(int i = 0; i < n - 1; ++i) {
        if(marked[i]) continue;
        auto [a, b, c] = edges[i];
        int A = dsu.findSet(a);
        int B = dsu.findSet(b);
        pairs.back() += dsu.join(A, B, pre[a] ^ pre[b] ^ pre[A] ^ pre[B] ^ c);
    }
    
    for(int i = n - 2; i >= 0; --i) {
        auto [a, b, c] = edges[p[i]];
        int A = dsu.findSet(a);
        int B = dsu.findSet(b);
        pairs[i] = pairs[i + 1] + dsu.join(A, B, pre[a] ^ pre[b] ^ pre[A] ^ pre[B] ^ c);
    }
    
    for(i64 v : pairs) cout << v << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
