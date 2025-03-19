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

int query(int k, string& s) {
	int cnt;
	cout << "? " << k + 1 << ' ' << s << '\n';
	cout.flush();
	cin >> cnt;
	return cnt;
}

void solve() {
	int n;

	cin >> n;

	vector<ii> wins(n);
	string src(n, '0');

	for(int i = 0; i < n; ++i) {
		string s(n, '0');
		for(int j = 0; j < n; ++j) s[j] = '0' + (i != j);
		wins[i] = {query(i, s), i};
	}

	sort(rall(wins));

	src[wins[0].sc] = '1';

	for(int i = 1; i < n; ++i) {
		auto [w, k] = wins[i];
		string s(n, '0');
		for(int j = 0; j < n; ++j) s[j] = k == j || src[j] == '1' ? '0' : '1';
		int nc = count(all(s), '0');
		if((nc == n && w > 0) || (nc < n && query(k, s) < w)) 
			for(int j = 0; j <= i; ++j) src[wins[j].sc] = '1';	
	}

	cout << "! " << src << '\n';
	cout.flush();
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
