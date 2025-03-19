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
using i128 = __int128;

void solve() {
	int n, m;

	cin >> n;

	vector<int> a(n), b(n), lo(n), color(n + 1, 0);
	vector<ii> st;
	map<int, int> x;
	map<int, vector<int>> type;

	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;

	st.pb({INF + 1, n});

	for(int i = n - 1; i >= 0; --i) {
		type[b[i]].pb(i);
		while(!st.empty() && st.back().fi <= b[i]) st.pop_back();
		lo[i] = st.back().sc;
		st.pb({b[i], i});
	}
	
	cin >> m;

	while(m--) {
		int c;
		cin >> c;
		++x[c];
	}

	for(int i = 0; i < n; ++i) {
		if(a[i] < b[i]) {
			cout << "NO\n";
			return;
		}
	}
	
	for(auto& [c, s] : type) {
		int m = s.size();
		reverse(all(s));
		int nc = color[s[0]] = a[s[0]] != b[s[0]];
		for(int k = 1; k < m; ++k) {
			int pos = s[k], last = s[k - 1];
			if(a[pos] == b[pos]) color[pos] = lo[last] >= pos && color[last];
			else if(lo[last] < pos || !color[last]) color[pos] = 1, ++nc;
			else color[pos] = lo[last] >= pos && color[last];
		}
		if(x[c] < nc) {
			cout << "NO\n";
			return;
		}
	}

	cout << "YES\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
