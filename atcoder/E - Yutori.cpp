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
	
	int n, k, c;
	string s;

	cin >> n >> k >> c >> s;

	vector<bool> work(n, true);	
	vector<int> a(n), b(n), days;
	queue<int> q;
	bool ok = false;

	for(int i = 0; i < n; ++i) {
		if(s[i] != 'o') continue;
		a[i] = 1;
		days.push_back(i);
		work[i] = !ok;
		if(days[0] < i - c) {
			int k = lower_bound(days.begin(), days.end(), i - c) - days.begin() - 1;
			a[i] += a[days[k]];
		}
		ok = ok || a[i] >= k;
	}

	ok = false;
	for(int i = n - 1; i >= 0; --i) {
		if(s[i] != 'o') continue;
		while(!q.empty() && q.front() - i > c) q.pop();
		if(!q.empty() || ok) work[i] = false;
		b[i] = 1;
		if(days.back() > i + c) {
			int k = upper_bound(days.begin(), days.end(), i + c) - days.begin();
			b[i] += b[days[k]];
		}
		if(a[i] + b[i] - 1 >= k) q.push(i);
		ok = ok || b[i] >= k;
	}

	while(!q.empty()) q.pop();

	for(int i = 0; i < n; ++i) {
		if(s[i] != 'o') continue;
		while(!q.empty() && i - q.front() > c) q.pop();
		if(!q.empty()) work[i] = false;
		if(a[i] + b[i] - 1 >= k) q.push(i);
		if(days[0] < i - c && days.back() > i) {
			int lo = lower_bound(days.begin(), days.end(), i - c) - days.begin() - 1;
			int hi = upper_bound(days.begin(), days.end(), i) - days.begin();
			if(a[days[lo]] + b[days[hi]] >= k) work[i] = false;
		}
		if(work[i]) cout << 1 + i << '\n';
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
