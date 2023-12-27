#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void base(vector<i64>& A) {
	int n = A.size();
	for(int i = 60, j = 0; i >= 0; --i) {
		bool ok = false;
		for(int k = j; k < n; ++k) {
			if(A[k] & (1ll << i)) {
				ok = true;
				swap(A[k], A[j]);
				break;
			}
		}
		if(!ok) continue;
		for(int k = j + 1; k < n; ++k) {
			if(A[k] & (1ll << i))
				A[k] ^= A[j];
		}
		++j;
	}
}

void solve() {
	int n;

	cin >> n;

	vector<i64> a(n), b;
	string s;

	for(i64& v : a) cin >> v;

	cin >> s;

	for(int i = n - 1; i >= 0; --i) {
		if(s[i] == '1') {
			for(i64 x : b) if((a[i] ^ x) < a[i]) a[i] ^= x;
			if(a[i]) {
				cout << "1\n";
				return;
			}
		} else {
			b.push_back(a[i]);
			base(b);
		}
	}

	cout << "0\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
 
