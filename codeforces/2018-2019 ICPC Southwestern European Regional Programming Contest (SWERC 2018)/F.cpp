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

using T = tuple<int, int, int>;

vector<T> p;

i64 cross(ii a, ii b) {
	auto [ax, ay] = a;
	auto [bx, by] = b;
	return (i64)ax * by - (i64)ay * bx;
}

int sign(int x) {
	return x >= 0 ? 1 : -1;
}

bool cmp(T a, T b) {
	auto [ax, ay, ag] = a;
	auto [bx, by, bg] = b;
	if(sign(ax) != sign(bx)) return sign(ax) > sign(bx);
	return cross({ax, ay}, {bx, by}) > 0;
}

void solve() {
	int n;
	
	cin >> n;
	
	p.resize(n);
	
	for(auto& [x, y, g] : p) cin >> x >> y >> g;
		
	if(n <= 2) {
		cout << "0\n";
		return;
	}
	
	vector<T> a(2 * (n - 1));
	vector<i64> pre(2 * (n - 1) + 1);
	
	i64 ans = LLONG_MAX;
	
	for(int i = 0; i < n; ++i) {
		int k = 0;
		
		auto [x0, y0, g0] = p[i];
		
		for(int j = 0; j < n; ++j) {
			if(i == j) continue;
			auto [x1, y1, g1] = p[j];
			a[k++] = {x1 - x0, y1 - y0, g1};
		}
		
		sort(a.begin(), a.begin() + n - 1, cmp);
		for(int j = 0; j < n - 1; ++j) a[j + n - 1] = a[j];
		
		pre[0] = 0;
		for(int j = 1; j <= 2 * (n - 1); ++j) pre[j] = pre[j - 1] + get<2>(a[j - 1]);
		
		for(int k = 0, j = 0; j < n - 1; ++j) {
			auto [ax, ay, ga] = a[j];
			
			while(k + 1 < j + n - 1) {
				auto [bx, by, gb] = a[k + 1];
				if(cross({ax, ay}, {bx, by}) < 0) break;
				++k;
			}
			
			i64 A = 0, B = 0;
			A += pre[k + 1] - pre[j];
			B += pre[j + n] - pre[k + 1];
			ans = min(ans, abs(A - B));
		}
	}
	
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


