#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;

void solve() {
	
	int n;

	cin >> n;

	set<int> S;

	while(n--) {
		int x;
		cin >> x;
		S.insert(x);
	}

	int K = *S.rbegin() - *S.begin() + 1;

	cout << K - (int)S.size() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

