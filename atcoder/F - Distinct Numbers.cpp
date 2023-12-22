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

	vector<int> f(n + 1, 0);
	int m = 0;	
	
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		++f[x];
	}

	for(int i = 0; i <= n; ++i) m += f[i] > 0;

	vector<int> pre(n + 1, 0);

	for(int i = 1; i <= n; ++i) ++pre[f[i]];
	for(int i = 1; i <= n; ++i) pre[i] += pre[i - 1];

	int maxn = n, t = n;

	for(int i = 1; i <= n; ++i) {

		if(m < i) {
			cout << "0\n";
			continue;
		}
	
		while(t / i < maxn) {
			t -= pre[n] - pre[maxn - 1];
			--maxn;	
		}

		cout << maxn << '\n';
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
