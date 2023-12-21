#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, x;
	set<int> P;
	multiset<int> X;
	cin >> x >> n;
	P.insert(0);
	P.insert(x);
	X.insert(x);
	for(int k = 0; k < n; ++k) {
		int p;
		cin >> p;
		auto high = P.upper_bound(p);
		auto low = prev(high);
		X.erase(X.find(*high - *low));
		X.insert(p - *low);
		X.insert(*high - p);
		P.insert(p);
		cout << *X.rbegin() << ' ';	
	}
	cout << '\n';
	return 0;
}
