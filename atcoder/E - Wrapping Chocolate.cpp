#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n, m;

	cin >> n >> m;

	multiset<int> Y;

	vector<ii> a(n), b(m);

	for(auto& [x, _] : a) cin >> x;
	for(auto& [_, y] : a) cin >> y;	
	for(auto& [x, _] : b) cin >> x;
	for(auto& [_, y] : b) cin >> y;

	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	int j = 0;

	for(int i = 0; i < m; ++i) {
		while(j < n && a[j].first <= b[i].first) Y.insert(a[j++].second);
		auto it = Y.upper_bound(b[i].second);
		if(it == Y.begin()) continue;
		Y.erase(prev(it));
	}	

	cout << (j == n && Y.empty() ? "Yes\n" : "No\n");
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}
