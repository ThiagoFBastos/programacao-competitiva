#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	int n, ans = INT_MAX;
	bool flag = true;

	cin >> n;

	vector<int> d(n + 1);
	int deg = 0, y = -1;

	for(int i = 3; i <= n; ++i) {
		cout << "? 1 " << i << '\n';
		cout.flush();
		cin >> d[i];
		if(d[i] != 1) continue;
		int x;
		cout << "? 2 " << i << '\n';
		cout.flush();
		cin >> x;
		ans = min(ans, x + 1);
		if(x != 2) flag = false;
		y = i, ++deg;
	}

  	if(!deg || (flag && deg > 1)) cout << "! 1\n";
	else if(!flag) cout << "! " << ans << '\n';
	else {
		for(int i = 3; i <= n; ++i) {
			if(d[i] != 2) continue;
			int x;
			cout << "? 2 " << i << '\n';
			cout.flush();
			cin >> x;
			if(x != 1) continue;
			cout << "? " << y << ' ' << i << '\n';	
			cout.flush();
			cin >> x;
			if(x == 1) {
				cout << "! 3\n";
				cout.flush();
				return;
			}
			break;
		}
		cout << "! 1\n";
	}
	cout.flush();
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
