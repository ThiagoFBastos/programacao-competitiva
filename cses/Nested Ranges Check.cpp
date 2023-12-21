#include "bits/stdc++.h"
using namespace std;
void solve() {
	int n;
	cin >> n;
	vector<tuple<int, int, int>> L(n), R(n);
	vector<int> a(n, 0), b(n, 0);
	multiset<int> X;
	int k = 0, j = 0, max_r = 0;
	for(int i = 0; i < n; ++i) {
		int l, r;
		cin >> l >> r;
		L[i] = {l, -r, i};
		R[i] = {r, -l, i};
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	while(k < n) {
		auto [la, ra, ia] = L[k];
		auto [rb, lb, ib] = R[j];
		if(la <= rb) {
			a[ia] = !X.empty() && *X.rbegin() >= -ra;
			X.insert(-ra);
			++k;
		} else {
			b[ib] = max_r >= -lb;
			max_r = max(max_r, -lb);
			X.erase(X.find(rb));
			++j;
		}
	}
	for(; j < n; ++j) {
		auto [rb, lb, ib] = R[j];
		b[ib] = max_r >= -lb;
		max_r = max(max_r, -lb);
	}
	for(int x : b) cout << x << ' ';
	cout << '\n';
	for(int x : a) cout << x << ' ';
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
