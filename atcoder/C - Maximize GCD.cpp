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

const int N = 3e5 + 1;
int cnt[N];

void solve() {
	int n;
	i64 k;
	cin >> n >> k;
	
	vector<int> a(n);
	i64 s = 0, ans = 1;
	
	for(int& v : a) {
		cin >> v;
		++cnt[v];
		s += v;
	}
	
	sort(a.begin(), a.end());
	
	for(int i = 1; i < N; ++i) cnt[i] += cnt[i - 1];
	
	for(int g = 2; g <= a.back(); ++g) {
		i64 y = s;
		
		for(int k = 0; k * g <= a.back(); ++k) {
			i64 x = cnt[min(a.back(), (k + 1) * g - 1)] - (k ? cnt[k * g - 1] : 0);
			y -= k * g * x;
			if(k) y += g * (0ll + cnt[k * g] - cnt[k * g - 1]);
		}

		y = (i64)n * g - y;
		
		if(y <= k) ans = g;
	}
	
	i64 y = 0;
	for(int v : a) y += a.back() - v;
	if(y <= k) ans = max(ans, a.back() + (k - y) / n);
	
	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

