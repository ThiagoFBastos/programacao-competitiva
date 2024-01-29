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
	int n;
		
	cin >> n;
	
	vector<string> local(n);
	vector<int> p(n), l(n), r(n);
	
	int minp = 0, maxp = 0;
	
	for(int i = 0; i < n; ++i) {
		cin >> local[i] >> p[i];
		p[i] *= 100;
		int R = min(10000, p[i] + 49), L = max(0, p[i] - 50);
		maxp += R;
		minp += L;
	}
	
	for(int i = 0; i < n; ++i) {
		int R = min(10000, p[i] + 49), L = max(0, p[i] - 50);
		
		l[i] = 10001;
		r[i] = -1;

		maxp -= R;
		minp -= L;
		
		for(int k = L; k <= R; ++k) {
			if(k + maxp >= 10000 && k + minp <= 10000) {
				l[i] = min(l[i], k);
				r[i] = max(r[i], k);
			}
		}

		if(l[i] > r[i]) {
			cout << "IMPOSSIBLE\n";
			return;
		}
		
		maxp += R;
		minp += L;
	}
	
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	
	for(int i = 0; i < n; ++i)
		cout << local[i] << ' ' << l[i] / 100.0 << ' ' << r[i] / 100.0 << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}


