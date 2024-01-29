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

	int a, b;

	cin >> a >> b;

	if(a > b) swap(a, b);

	int d = b - a;

	vector<int> G;

	for(int k = 2; k * k <= d; ++k) {
		if(d % k) continue;
		G.push_back(k);
		while(d % k == 0) d /= k;
	}

	if(d > 1) G.push_back(d);

	priority_queue<tuple<int, int, int>> q;
	set<ii> S;
	int ans = INT_MAX;

	q.emplace(0, a, b);
	

	while(!q.empty()) {
		auto [d, a, b] = q.top();

		q.pop();

		if(a == 1) {
			ans = min(ans, -d);
			continue;
		} else if(b - a == 1) {
			ans = min(ans, -d + a - 1);
			continue;
		}

		ans = min(ans, -d + a - 1);

		if(S.count(ii(a, b))) continue;		
		S.insert(ii(a, b));

		int diff = b - a;

		for(int k : G) {
			if(diff % k) continue;
			int mod = a % k;
			ii x((a-mod) / k, (b-mod) / k);
			if(!S.count(x)) q.emplace(d - mod - 1, (a-mod) / k, (b-mod) / k);
			int r = (k - mod) % k;
			ii y((a + r) / k, (b + r) / k);
			if(!S.count(y)) q.emplace(d - r - 1, (a + r) / k, (b + r) / k);
		}
	}

	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

