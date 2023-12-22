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

using mat = array<array<i64, 3>, 3>;
	
i64 L, A, B, p = 1;
int M, ans = 0;

void mul(mat& a, mat& b) {
	mat c;
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			c[i][j] = 0;
			for(int k = 0; k < 3; ++k) c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % M;
		}
	}
	swap(a, c);
}

void exp(mat& dst, mat& src, i64 p) {
	for(int i = 0; i < 3; ++i)
	for(int j = 0; j < 3; ++j)
		dst[i][j] = i == j;
	for(; p > 0; p >>= 1) {
		if(p & 1) mul(dst, src);
		mul(src, src);
	}
}

void solve() {
	cin >> L >> A >> B >> M;

	for(int k = 1; k <= 18; ++k) {
		if(A <= 10 * p - 1) {
			mat X, T;

			i64 i = (max(p, A) - A + B - 1) / B;
			i64 j = (min(10 * p - 1, A + B * (L - 1)) - A) / B;

			if(i <= j) {
				i64 lo = A + B * i;
				i64 hi = A + B * j;

				i64 n = (hi - lo) / B + 1;
				
				T[0][0] = 10 * p % M;
				T[0][1] = 1;
				T[0][2] = 1;
		
				T[1][0] = 0;
				T[1][1] = 1;
				T[1][2] = 1;

				T[2][0] = 0;
				T[2][1] = 0;
				T[2][2] = 1;
				
				exp(X, T, n);
		
				ans = (ans * X[0][0] % M + (lo - B) % M * X[0][1] % M + B % M * X[0][2] % M) % M;
			}
		}
		p *= 10;
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
}s
