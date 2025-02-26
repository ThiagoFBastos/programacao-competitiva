#include "bits/stdc++.h"

using namespace std;

#define INF    1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

void solve() {
    int n;

    cin >> n;   

    vector<vector<int>> adj(n);
    vector<i64> s(n), a(n), lo(n);

    for(int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        adj[p-1].pb(i);
    }

    for(i64& v : a) cin >> v;

    auto fix = [&](auto& self, int u)->bool {
        int sub = 0;
        i64 t = 0;
        for(int v : adj[u]) {
            sub += a[v] == 0;
            t += a[v];
        }
        if(!sub) return true;
        else if(sub == 1) {
            for(int v : adj[u]) {
                if(a[v]) continue;
                a[v] = a[u] - t;
                if(a[v] <= 0 || !self(self, v)) return false;
            }
        } else {
            for(int v : adj[u]) {
                if(a[v]) continue;
                a[v] = lo[v];
                if(!self(self, v)) return false;
            }
        }
        lo[u] = adj[u].empty() ? 1 : 0;
        for(int v : adj[u]) lo[u] += lo[v];
        if(a[u]) lo[u] = a[u];
        return true;
    };

    for(int i = n - 1; i >= 0; --i) {
        int sub = 0;
        i64 t = 0;
        for(int v : adj[i]) {
            sub += a[v] == 0;
            t += a[v];
        }
        if(sub == 0 && !a[i]) a[i] = t;
        if(a[i] && !fix(fix, i)) {
            cout << "impossible\n";
            return;
        }
        lo[i] = adj[i].empty() ? 1 : 0;
        for(int v : adj[i]) lo[i] += lo[v];
        if(a[i]) lo[i] = a[i];
    }

    for(int i = 0; i < n; ++i) if(adj[i].empty() && !a[i]) a[i] = 1;
    
    auto check = [&](auto& self, int u)->bool {
        s[u] = adj[u].empty() ? a[u] : 0;
        for(int v : adj[u]) {
            if(!self(self, v)) return false;
            s[u] += s[v];
        }
        return a[u] == 0 || a[u] == s[u];
    };

    if(!a[0] || !check(check, 0)) {
        cout << "impossible\n";
        return;
    }

    for(i64 v : s) cout << v << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
//  cin >> t;
    while(t--) solve();
    return 0;
}