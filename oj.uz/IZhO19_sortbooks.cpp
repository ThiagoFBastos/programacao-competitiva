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
 
void solve() {
	int n, m;
	vector<ii> in;
	set<ii> out;
 
	cin >> n >> m;
 
	vector<int> w(n);
	vector<bool> can(m, false);
 
	for(int& v : w) cin >> v;
 
	vector<tuple<int, int, int, int>> query(m);
 
	for(int i = 0; i < m; ++i) {
		int l, r, k;
		cin >> l >> r >> k;
		--l, --r;
		query[i] = {r, l, k, i};
	}
 
	sort(all(query));
 
	for(int i = 0, j = 0; i < n; ++i) {
		vector<ii> tmp;
 
		while(!in.empty() && in.back().sc <= w[i]) {
			tmp.pb(in.back());
			in.pop_back();
		}
 
		reverse(all(tmp));
 
		for(int j = 0; j < (int)tmp.size() - 1; ++j) {
			tmp[j].sc += tmp[j + 1].sc;
			if(auto it = out.lower_bound(ii(tmp[j].fi, -1)); it == out.end() || tmp[j].sc > it->sc) {
				it = out.insert(tmp[j]).fi;
				while(it != out.begin() && prev(it)->sc <= it->sc) it = out.erase(prev(it));
			}
		}
 
		in.pb({i, w[i]});
 
		while(j < m && get<0>(query[j]) == i) {
			auto [r, l, k, pos] = query[j++];
 
			auto i1 = lower_bound(all(in), ii(l, -1));
 
			int mood = 0;
 
			if(in.end() - i1 >= 2) mood = i1->sc + next(i1)->sc;
			
			auto i2 = out.lower_bound(ii(l, -1));
 
			if(i2 != out.end()) mood = max(mood, i2->sc);
 
			can[pos] = mood <= k;
		}
	}
 
	for(bool x : can) cout << x << '\n';
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
