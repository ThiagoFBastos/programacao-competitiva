#pragma GCC optimize("O3,unroll-loops")
 
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
 
const int N = 2e3, inf = 1e9;
 
bitset<101> dp[101];
int n, l, r, DP[N], a[N];
 
bool sub1(i64 mask, i64 X) {
	
	fill(DP, DP + n, inf);
				
	i64 S = mask | X, pre = 0;
				
	for(int i = 0; i < n; ++i) {
		pre += a[i];
		
		if((pre & ~S) <= X) DP[i] = 1;
		
		i64 s = 0;
		
		for(int j = i + 1; j < n; ++j) {
			s += a[j];
			if((s & ~S) <= X) DP[j] = min(DP[j], DP[i] + 1);
		}
	}
	
	return DP[n - 1] <= r;
}
 
bool sub2(i64 mask, i64 X) {
 
	for(int i = 0; i < n; ++i) dp[i].reset();
				
	i64 S = mask | X, pre = 0;
				
	for(int i = 0; i < n; ++i) {
		pre += a[i];
		
		if((pre & ~S) <= X) dp[i][1] = 1;
		
		i64 s = a[i];
		
		for(int j = i - 1; j >= 0; --j) {
			if((s & ~S) <= X) dp[i] = dp[i] | (dp[j] << 1);
			s += a[j];
		}
	}
				
	for(int i = l; i <= r; ++i) if(dp[n - 1][i]) return true;
			
	return false;
}
 
void solve() {
	
	cin >> n >> l >> r;
 
	for(int i = 0; i < n; ++i) cin >> a[i];
	
	if(l == 1) {
		i64 mask = 0;
		
		for(int m = 41; m > 0; ) {
			if(sub1(mask, 0)) break;
			
			int lo = 0, hi = m - 1;
			
			while(lo < hi) {
				int mid = (lo + hi) / 2;
				if(sub1(mask, 1LL << mid)) hi = mid;
				else lo = mid + 1;
			}
			
			mask |= 1LL << hi;
			m = hi;
		}
		
		cout << mask << '\n';
	} else {
		i64 mask = 0;
		
		for(int m = 41; m > 0; ) {
			if(sub2(mask, 0)) break;
			for(int k = 0; k < m; ++k) {
				if(sub2(mask, 1LL << k)) {
					mask |= 1LL << k;
					m = k;
					break;
				}
			}
		}
		
		cout << mask << '\n';
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
