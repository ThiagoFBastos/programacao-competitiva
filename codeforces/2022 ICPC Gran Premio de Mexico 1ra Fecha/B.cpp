#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
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

const int N = 1e5 + 100;

vector<int> adj[N];
int n, k, in[N], out[N], depth[N], tms, par[N];
ii st[2 * N];

ii query(int l, int r) {
    ii ans = {INF, INF};
    l += n;
    r += n;
    while(l <= r) {
        if(l & 1) ans = min(ans, st[l++]);
        if(~r & 1) ans = min(ans, st[r--]);
        l /= 2;
        r /= 2;
    }
    return ans;
}

void upd(int k) {
    k += n;
    st[k] = {INF, INF};
    for(k /= 2; k; k /= 2) st[k] = min(st[2 * k], st[2 * k + 1]);
}

void dfs(int u, int p = -1) {
    par[u] = p;
    st[tms + n] = ii(depth[u], u);
    in[u] = tms++;
    for(int v : adj[u]) {
        if(v == p) continue;
        depth[v] = 1 + depth[u];
        dfs(v, u);
    }
    out[u] = tms - 1;    
}

void solve() {
    cin >> n >> k;
    
    for(int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    dfs(0);
    
    for(int i = n - 1; i; --i) st[i] = min(st[2 * i], st[2 * i + 1]);
    
    vector<int> p;
    set<int> S;
    
    S.insert(0);
    
    upd(0);
    
    while(!S.empty()) {
        int u = *S.begin(), up = 0;
        
        S.erase(S.begin());
        
        p.pb(u + 1);
   
        while(up < k && u != -1) {
            while(true) {
                auto [d, v] = query(in[u], out[u]);
                if(up + d - depth[u] > k) break;
                S.insert(v);
                upd(in[v]);
            }
            u = par[u];
            ++up;
        }
    }
    
    for(int v : p) cout << v << ' ';
    cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}


