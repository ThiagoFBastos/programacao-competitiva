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
	int n;
	
	cin >> n;

	vector<int> a(n), hi(n);
	vector<ii> st, pairs;
	int bad = n;
	set<ii> S;
	set<int> R;
	
	for(int& v : a) cin >> v;
	
	a.pb(INF);

	st.pb({-INF, n});

	for(int i = n - 1; i >= 0; --i) {
		while(!st.empty() && st.back().fi >= a[i]) st.pop_back();
		hi[i] = st.back().sc - 1;
		st.pb({a[i], i});
	}

	st.clear();

	for(int i = n - 1; i >= 0; --i) {
		if(a[i] + 1 == a[i + 1]) bad = i;

		while(!st.empty() && st.back().fi <= a[i]) {
			st.back().fi = st.back().sc - st.back().fi;
			S.erase(st.back());			
			st.pop_back();
		}

		auto it = S.lower_bound(ii(i - a[i], -1));
		
		if(it != S.end() && it->first == i - a[i] && it->second <= min(bad, hi[i])) {
			int r = it->second;
			if(R.empty() || *R.begin() > r) {
				R.insert(r);
				pairs.pb({i+1,r+1});
			}
		}
		
		st.pb({a[i], i});
		S.emplace(i - a[i], i);
	}

	reverse(all(pairs));

	cout << pairs.size() << '\n';
	for(auto [x, y] : pairs) cout << x << ' ' << y << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 // cin >> t;
	while(t--) solve();
	return 0;
}
