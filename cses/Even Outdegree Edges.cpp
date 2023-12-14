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
 
vector<int> adj[N], usable[N];
int n, m, in[N], tms;
vector<ii> ed;
 
bool dfs(int u, int p) {
	m += adj[u].size();
 
	in[u] = tms++;
 
	for(int v : adj[u]) {
		if(in[v] < 0) {
			 if(!dfs(v, u)) usable[u].pb(v);
		} else if(in[v] > in[u]) usable[u].pb(v);
	}
 
	int par = usable[u].size() % 2;
	while((int)usable[u].size() > par) {
		int v = usable[u].back();
		ed.pb({u + 1, v + 1});
		usable[u].pop_back();
	}
 
	if((int)usable[u].size() == 1) {
		ed.pb({u + 1, p + 1});
		ed.pb({u + 1, usable[u][0] + 1});
		return true;
	}
 
	return false;
}
 
void solve() {
	cin >> n >> m;
 
	memset(in, -1, sizeof in);
 
	while(m--) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
 
	for(int i = 0; i < n; ++i) {
		if(in[i] != -1) continue;
		m = 0;
		dfs(i, i);
		if(m % 4) {
			cout << "IMPOSSIBLE\n";
			return;
		}
	}
 
	for(auto [a, b] : ed) cout << a << ' ' << b << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}
