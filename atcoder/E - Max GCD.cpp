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
	int n, k;
	
	cin >> n >> k;
	
	vector<int> a(n);
	i64 s = 0;
	
	for(int& v : a) {
		cin >> v;
		s += v;
	}
	
	vector<int> divisores;
	
	for(int k = 1; k * k <= s; ++k) {
		if(s % k) continue;
		divisores.push_back(k);
		divisores.push_back(s / k);
	}
	
	sort(divisores.rbegin(), divisores.rend());
	
	for(int p : divisores) {
		i64 ans = LLONG_MAX, X = 0, Y = 0;
		vector<int> P;
		for(int x : a) {
			P.push_back(x % p);
			Y += p - P.back();
		}
		sort(P.begin(), P.end());
		for(int i = 0; i < n; ++i) {
			ans = min(ans, max(X, Y));
			Y -= p - P[i];
			X += P[i];
		}
		if(ans <= k) {
			cout << p << '\n';
			break;
		}
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

