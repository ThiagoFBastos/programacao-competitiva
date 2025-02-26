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

const double eps = 1e-15L;
const int N = 20;

double e[2][N][N], p[2][N][N];

void solve() {
    
    int n, m, u, v;
    
    cin >> n >> m;
    
    vector<vector<int>> g(n);
    vector<int> odd(n, 0);

    while(m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    cin >> u >> v;
    
    if(u == v) {
        cout << "0\n";
        return;
    }
    
    function<bool(int)> dfs = [&](int x) {
        bool bip = true;
        for(int y : g[x]) {
            if(!odd[y]) {
                odd[y] = -odd[x];
                bip = dfs(y) && bip;
            } else if(odd[x] == odd[y]) bip = false;
        }
        return bip;
    };
    
    odd[u] = -1;
    bool bip = dfs(u);
    
    if(!odd[v] || bip && odd[u] != odd[v]) {
        cout << "never meet\n";
        return;
    }

    double expc = 0;
    
    p[0][u][v] = 1.0;
    
    while(true) {
        bool flag = false;
        
        for(int u = 0; u < n; ++u) {
            for(int v = 0; v < n; ++v) {
                flag = flag || p[0][u][v] > eps;
                e[1][u][v] = p[1][u][v] = 0;
            }
        }
        
        if(!flag) break;
        
        for(int u = 0; u < n; ++u) {
            for(int v = 0; v < n; ++v) {
                if(u == v) continue;
                int P = g[u].size(), Q = g[v].size();
                for(int x : g[u]) {
                    for(int y : g[v]) {
                        p[1][x][y] += p[0][u][v] / (P * Q);
                        e[1][x][y] += (e[0][u][v] + p[0][u][v]) / (P * Q);
                    }
                }
            }
        }
        
        for(int u = 0; u < n; ++u) {
            expc += e[1][u][u];
            for(int v = 0; v < n; ++v) {
                if(u == v) continue;
                e[0][u][v] = e[1][u][v];
                p[0][u][v] = p[1][u][v];
            }
        }
    }

    cout << fixed << setprecision(10) << expc << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}