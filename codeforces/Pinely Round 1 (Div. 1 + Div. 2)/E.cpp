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

const int N = 4e3 + 10;

vector<int> adj[N];
bool vis[N];

void solve() {
	int n;
	vector<vector<int>> CC;

	cin >> n;

	for(int i = 0; i < n; ++i) {
		adj[i].clear();
		vis[i] = false;
	}

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < n; ++j) if(s[j] == '1') adj[i].pb(j);
	}

	for(int i = 0; i < n; ++i) {
		if(vis[i]) continue;

		queue<int> q;
		int edges = 0;
		ii who(INF, INF);

		CC.pb({});

		vis[i] = true;
		q.push(i);

		while(!q.empty()) {
			int u = q.front(); q.pop();
			CC.back().pb(u);
			edges += adj[u].size();
			who = min(who, ii((int)adj[u].size(), u));
			for(int v : adj[u]) {
				if(vis[v]) continue;
				vis[v] = true;
				q.push(v);
			}
		}

		int m = CC.back().size();

		if(m == n) {
			cout << "0\n";
			return;
		}

		if(edges == 0 || edges < m * (m - 1)) {
			cout << "1\n";
			cout << who.sc + 1 << '\n';
			return;
		}
	}

	if((int)CC.size() >= 3) {
		cout << "2\n";
		cout << CC[0][0] + 1 << ' ' << CC[1][0] + 1 << '\n';
	} else {
		if(CC[0].size() > CC[1].size()) swap(CC[0], CC[1]);
		cout << CC[0].size() << '\n';
		for(int v : CC[0]) cout << v + 1 << ' ';
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


