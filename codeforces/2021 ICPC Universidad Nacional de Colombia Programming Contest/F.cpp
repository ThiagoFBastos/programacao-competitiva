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

const int N = 5e3 + 10;
const int M = N * N + N;

int row[N], col[N];
int dat[M], *A;
int lo, shift = 0, n, q;

void solve() {
	
	cin >> n >> q;

	A = &dat[M - n * n];
	lo = M - n * n;

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for(int j = 0; j < n; ++j) {
			A[i * n + j] = s[j] - '0';
			row[i] += s[j] - '0';
			col[j] += s[j] - '0';
		}
	}
	
	while(q--) {
		int t, i, j, b;
		cin >> t;
		if(t == 1) {
			cin >> i >> j >> b;
			--i, --j;
			row[i] += b - A[i * n + j];
			col[(j - shift + n) % n] += b - A[i * n + j];
			A[i * n + j] = b;
		} else {
			cin >> b;
			row[0] += b;
			for(int k = 0; k < n; ++k) {
				row[k] -= A[k * n + n - 1];
				if(k) row[k] += A[(k - 1) * n + n - 1];
			}
			shift = (shift + 1) % n;
			col[(n - shift) % n] += b - A[(n - 1) * n + n - 1];
			A = &dat[--lo];
			A[0] = b;
		}

		int ans = 0;
		for(int i = 0; i < n; ++i) ans += (row[i] == n) + (col[i] == n);
		cout << ans << '\n';
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

