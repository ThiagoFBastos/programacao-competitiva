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

const int sz = 320, N = 1e5 + 320;

int GCD[sz], a[N];

void solve() {
	int q, n = 0;
	map<int, vector<int>> S;
	
	cin >> q;
	
	while(q--) {
		char t;
		int x;
		cin >> t >> x;
		if(t == '+') {
			int i = n++;
			a[i] = x;
			GCD[i / sz] = gcd(GCD[i / sz], x);
			S[x].push_back(i);
		} else {
			auto& v = S[x];
			int i = v.back();
			v.pop_back();
			GCD[i / sz] = a[i] = 0;
			for(int k = 0; k < sz; ++k) GCD[i / sz] = gcd(GCD[i / sz], a[k + i / sz * sz]);
		}
		int g = 0;
		for(int i = 0; i < sz; ++i) g = gcd(g, GCD[i]);
		cout << max(1, g) << '\n';
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