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

const int N = 4e6 + 100;
const int skip = 2e6;

int cnt[N], frq[N], SUF[N];
vector<int> value[N];

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n), last(n, -1), suf(n + 1, 0);
  	int X = 0, ans = 0;

	for(int& v : a) {
		cin >> v;
    	v += skip;
		X = max(X, ++cnt[v]);
	}

	if(k == 0) {
		cout << X << '\n';
		return;
	}

	for(int i = 0; i < n; ++i) {
		suf[i] = cnt[a[i]] - frq[a[i]] + frq[a[i] - k];
		++frq[a[i]];
	}

	for(int i = n - 1; i >= 0; --i) {
		suf[i] = max(suf[i], SUF[a[i]]);
		SUF[a[i]] = max(suf[i], SUF[a[i]]);

		auto& v = value[a[i]];

		while(!v.empty() && v.back() <= suf[i]) v.pop_back();

		v.push_back(suf[i]);

		if(!value[a[i] + k].empty()) last[i] = value[a[i] + k].back();
	}

	memset(frq, 0, sizeof frq);

	for(int i = 0; i < n; ++i) {
		if(last[i] != -1) ans = max(ans, last[i] - frq[a[i]] + frq[a[i] + k]);
		++frq[a[i]];
		ans = max(ans, frq[a[i]] + cnt[a[i] - k] - frq[a[i] - k]);
	}

	cout << max(ans, X) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

