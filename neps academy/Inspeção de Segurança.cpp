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

int n, k;
vector<int> a, b;

bool inspeciona(i64 T) {
	i64 t = 0, cnt = 0;
	for(int k = n - 1; k >= 0; --k) {
		if(t == 0) t += a[k];
		if(t + b[k] <= T) t += b[k];
		else {
			int B = b[k] - T + t;
			cnt += 1 + B / (T - a[k]);
			if(B % (T - a[k])) t = a[k] + B % (T - a[k]);
			else t = 0;
		}
	}
	return cnt + (t > 0) <= k;
}

void solve() {
	cin >> n >> k;
	
	a.resize(n);
	b.resize(n);
	
	i64 lo = 0, hi = 0;
	
	for(int& v : a) cin >> v;
		
	for(int& v : b) {
		cin >> v;
		hi += v;
	}
	
	lo = a.back() + 1;
	hi += a.back();
	
	while(lo < hi) {
		i64 mid = (lo + hi) / 2;
		if(inspeciona(mid)) hi = mid;
		else lo = mid + 1;
	}
	
	cout << hi << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}