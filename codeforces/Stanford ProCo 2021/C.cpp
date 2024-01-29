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
	int s, n, q;
	
	cin >> s >> n;
	
	vector<int> a(n), b;
	
	for(int& v : a) cin >> v;
	
	sort(a.begin(), a.end());
	
	b = a;
	b.resize(unique(b.begin(), b.end()) - b.begin());
	
	vector<int> cnt(b.size());
	
	for(int i = 0; i < (int)b.size(); ++i) {
		int k = upper_bound(a.begin(), a.end(), b[i]) - a.begin();
		cnt[i] = k;
	}
	
	cin >> q;
	
	while(q--) {
		int x;
		cin >> x;
		int i = upper_bound(cnt.begin(), cnt.end(), x) - cnt.begin();
		if(i == (int)b.size()) cout << s << '\n';
		else cout << b[i] - 1 << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}


