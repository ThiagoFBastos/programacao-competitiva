#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
struct customer {
	int arrival, pos;
	bool type;
};
bool operator<(customer a, customer b) {
	return a.arrival < b.arrival || (a.arrival == b.arrival && a.type && !b.type);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, r[MAXN];
	cin >> n;
	vector<customer> C;
	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		C.push_back({a, i, true});
		C.push_back({b, i, false});
	}
	sort(C.begin(), C.end());
	set<int> S;
	for(int k = 1; k <= n; ++k) S.insert(k);
	for(int i = 0; i < C.size(); ++i) {
		auto [a, k, t] = C[i];
		if(t) {
			r[k] = *S.begin();
			S.erase(S.begin());
		}
		else
			S.insert(r[k]);
	}
	cout << *max_element(r, r + n) << '\n';
	for(int k = 0; k < n; ++k) cout << r[k] << ' ';
	cout << '\n';
	return 0;
}
