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

	vector<int> a(n);
	
	for(int& v : a) cin >> v;

	set<int> st;
	vector<int> start(n + 1, -1);

	for(int i = 1; i <= n; ++i) st.insert(i);

	for(int i = 1; i < n; ++i) {
		if(a[i - 1] > a[i]) {
			auto it = st.lower_bound(a[i - 1] - a[i]);
			start[*it] = i;
			st.erase(it);
		}
	}

	for(int x : st) start[x] = n - 1;

	for(int i = 1; i <= n; ++i) cout << start[i] + 1 << ' ';
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
