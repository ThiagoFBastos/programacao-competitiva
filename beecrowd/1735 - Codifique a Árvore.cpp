#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
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
//using i128 = __int128;

vector<int> prufer_code(vector<vector<int>>& adj, int n) {
	vector<int> code, deg(n, 0);
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 0; i < n; ++i) {
		deg[i] = adj[i].size();
		if(deg[i] == 1) pq.push(i);
	}
	while(!pq.empty()) {
		int u = pq.top(); pq.pop();
		for(int v : adj[u]) {
			if(deg[v] == 1) continue;
			code.pb(v);
			if(--deg[v] == 1) pq.push(v);
		}
	}
	return code;
}

void solve() {
	string s;

	while(getline(cin, s)) {
	
		vector<vector<int>> adj(50);
		int n = 0;
		stack<int> st;

		for(int i = 0; i < (int)s.size(); ++i) {
			if(s[i] == ')') st.pop();
			else if(isdigit(s[i])) {
				int x = s[i] - '0';
				if(isdigit(s[i + 1])) {
					x *= 10;
					x += s[i + 1] - '0';
					++i;
				}
				n = max(n, x);
				--x;
				if(!st.empty()) {
					adj[st.top()].pb(x);
					adj[x].pb(st.top());
				}
				st.push(x);
			}
		}

		auto code = prufer_code(adj, n);
		
		if(n > 1) {
			code.pb(n - 1);
			for(int i = 0; i < (int)code.size() - 1; ++i) cout << code[i] + 1 << ' ';
			cout << code.back() + 1 << '\n';
		} else
			cout << "\n";
	}
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}