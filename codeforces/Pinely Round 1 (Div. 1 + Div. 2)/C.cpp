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

const int N = 1e2 + 10;

vector<int> adj[N];
set<int> S[N];
bool vis[N];
int n, cur;

void dfs(int u) {
	vis[u] = true;
	for(int v : adj[u]) {
		if(!vis[v]) dfs(v);
		for(int x : S[v]) S[u].insert(x);
	}
	S[u].insert(cur);
	cur++;
}

void solve() {
	cin >> n;

	for(int i = 0; i < n; ++i) {
		adj[i].clear();
		S[i].clear();
		vis[i] = false;
	}

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < n; ++j) if(s[j] == '1') adj[j].pb(i);
	}

	cur = 1;
	for(int i = 0; i < n; ++i) if(!vis[i]) dfs(i);

	for(int i = 0; i < n; ++i) {
		cout << S[i].size();
		for(int x : S[i]) cout << ' ' << x;
		cout << '\n';
	}
}	

int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


