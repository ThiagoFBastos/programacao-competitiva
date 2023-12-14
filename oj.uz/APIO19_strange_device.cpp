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
/*
	t1 < t2
	
	t2 = t1 + Bk
	
	t1 + t1 / B = t1 + Bk + (t1 + Bk) / B mod A
	
	t1 / B = Bk + (t1 + Bk) / B mod A
	
	t1 / B = Bk + t1 / B + k mod A
	
	0 = Bk + k mod A
	
	0 = k(B + 1) mod A
	
	C = AB/gcd(A, B + 1)
	
	t2 = t1 + Ck'
	
	t2 = t1 mod C
*/
 
	int n;
	i64 A, B;
	
	cin >> n >> A >> B;
	
	__int128 C = (__int128)A * B / gcd(A, B + 1);
	
	vector<pair<i64, int>> sweep;
	
	for(int i = 0; i < n; ++i) {
		i64 l, r;
		cin >> l >> r;
		
		if(r - l + 1 >= C) {
			sweep.push_back({0, 1});
			sweep.push_back({C, -1});
			continue;
		}
		
		i64 L = l % C, R = r % C;
 
		if(L <= R) {
			sweep.push_back({L, 1});
			sweep.push_back({R + 1, -1});
		} else {
			sweep.push_back({L, 1});
			sweep.push_back({C, -1});
			sweep.push_back({0, 1});
			sweep.push_back({R + 1, -1});
		}
	}
	
	sort(sweep.begin(), sweep.end());
	
	i64 ans = 0;
	int abertos = 0;
	
	for(int i = 0; i < (int)size(sweep); ++i) {
		auto [x, type] = sweep[i];
		if(abertos) ans += x - sweep[i - 1].first;
		abertos += type;
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
