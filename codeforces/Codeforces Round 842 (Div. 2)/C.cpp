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
	int n;

	cin >> n;

	vector<int> frq(n + 1, 0);
	vector<int> p(n, -1), q(n, -1), a(n);
	vector<vector<ii>> S(3);
	
	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		++frq[a[i]];
	}

	if(*max_element(all(frq)) > 2) {
		cout << "NO\n";
		return;
	}

	for(int i = 0; i < n; ++i) {
		if(frq[a[i]] == 2) 
			S[2].pb({a[i], i});
		else if(frq[a[i]] == 1)
			p[i] = q[i] = a[i];
	}
	
	sort(rall(S[2]));

	for(int i = n; i; --i) {
		if(frq[i] == 0) {
			S[0].pb({i, -1});
			S[0].pb({i, -1});
		}
	}

	while(!S[0].empty()) {
		for(int i = 0; i < 2; ++i) {
			auto [x, k] = S[0].back();
			auto [y, j] = S[2].back();
			S[0].pop_back();
			S[2].pop_back();
			if(y < x) {
				cout << "NO\n";
				return;
			}
			if(i == 0) p[j] = x, q[j] = y;
			else q[j] = x, p[j] = y;
		}
	}

	cout << "YES\n";
	for(int v : p) cout << v <<  ' ';
	cout << '\n';
	for(int v : q) cout << v <<  ' ';
	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
