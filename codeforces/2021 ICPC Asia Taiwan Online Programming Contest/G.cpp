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
	
	vector<i64> cnt(n, 1), copia(n, 0);
	map<int, vector<ii>> S;
			
	for(int i = 0; i < n - 1; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a, --b;
		S[c].emplace_back(a, b);
	}

	for(auto& [l, e] : S) {
		for(auto [a, b] : e) {
			copia[b] += cnt[a];
			copia[a] += cnt[b];
		}
		for(auto [a, b] : e) {
			cnt[b] += copia[b];
			cnt[a] += copia[a];
			copia[a] = copia[b] = 0;
		}
	}

	cout << accumulate(cnt.begin(), cnt.end(), 0LL) - n << '\n';
}

int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}

