#include "bits/stdc++.h"
using namespace std;
const int mod = 9901, MAXN = 301;
int fat[MAXN], e[15][2], n, k;
bool number_of_sets(int mask, int& sets, int& var) {
    vector<int> pai(n, -1);
    sets = var = 0;
    for(int v = 0; v < n; ++v) {
        if(pai[v] != -1) continue;
        bool ok = false;
        for(int i = 0; i < k; ++i) {
            if(!(mask & 1 << i)) continue;
            for(int j = 0; j < 2; ++j)
                if(e[i][j] == v) ok = true;
        }
        if(!ok) continue;
        queue<int> q;
        int vc = 0, edges = 0, d1 = n + 1, d2 = 0;
        ++sets;
        pai[v] = v;
        q.push(v);
        while(!q.empty()) {
            int u = q.front(), deg = 0;
            q.pop();
            ++vc;
            for(int i = 0; i < k; ++i) {
                if(!(mask & 1 << i)) continue;
                for(int j = 0; j < 2; ++j) {
                    if(e[i][j] != u) continue;
                    ++deg;
                    int b = e[i][j ^ 1];
                    if(pai[b] == -1) {
                        pai[b] = u;
                        q.push(b);
                    }
                }
            }
            d1 = min(d1, deg);
            d2 = max(d2, deg);
            edges += deg;
        }
        edges /= 2;
        if(d2 > 2 || edges > vc) return false;
        else if(edges == vc && d1 != d2) return false;
        else if(edges == vc && vc != n) return false;
        var += vc;
    }
    return true;
}
void solve() {
    cin >> n >> k;
    for(int i = 0; i < k; ++i) {
    for(int j = 0; j < 2; ++j) {
        cin >> e[i][j];
        --e[i][j];
    }}
    int cnt = fat[n - 1] / 2;
    for(int mask = 1; mask < (1 << k); ++mask) {
        int ns, nv;
        if(number_of_sets(mask, ns, nv)) {
            int ciclos = 1, arestas = 1;
            for(int i = 0; i < ns - 1; ++i) {
                ciclos = arestas * 2 * ciclos % mod;    
                ++arestas;
            }
            for(int i = 0; i < n - nv; ++i) {
                ciclos = arestas * ciclos % mod;
                ++arestas;
            }
            cnt = (cnt - (__builtin_popcount(mask) & 1 ? 1 : -1) * ciclos) % mod;
        }
    }
    cout << (cnt + mod) % mod << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    fat[0] = 1;
    for(int k = 1; k < MAXN; ++k) fat[k] = k * fat[k - 1] % mod;
    int t;
    cin >> t;
    for(int i = 1; i <= t; ++i) {
        cout << "Case #" << i << ": "; 
        solve();
    }
    return 0;
}