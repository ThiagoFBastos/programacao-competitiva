#include "bits/stdc++.h"
using namespace std;
bool primo(long long x) {
	if(x < 2) return false;
	for(auto k = 2LL; k * k <= x; ++k) if(x % k == 0) return false;
	return true;
}
void solve() {
	long long z, k, v = 0;
	cin >> z;
	long long sqr = sqrt(z);
	vector<long long> p;
	for(auto x = sqr + 300; x > 1; --x) {
		if(!primo(x)) continue;
		p.push_back(x);
		if(size(p) >= 2 && p[size(p) - 2] <= sqr) break;
	}
	for(int i = 0; i < int(size(p)) - 1; ++i) if(p[i] * p[i + 1] <= z) v = max(v, p[i] * p[i + 1]); 
	cout << v << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
	return 0;
}