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
	int n, q;
	i64 ans = 0;

	cin >> n >> q;

	vector<int> a(n);
	for(int& v : a) cin >> v;
	
	while(q--) {
		int x, y;
		i64 z;

		cin >> x >> y >> z;
		
		int l = ((x + ans - 1) % n + n) % n, r = ((y + ans - 1) % n + n) % n;
		i64 d = z + ans, v = 0;
	
		vector<int> b(a.begin() + l, a.begin() + r + 1);

		sort(b.begin(), b.end());

		i64 sum = 0;

		for(int i = 0; i < (int)b.size(); ++i) {
			sum += b[i];
			if(i + 1 < (int)b.size() && b[i] == b[i + 1]) continue;
			if(sum <= d) v = max(v, sum);
		}

		cout << v << '\n';

		ans = v;
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


