#include "bits/stdc++.h"
using namespace std;
int n;
void solve() {
	for(int i = 1; i < n; ++i) {
		int pos;
		cout << "M " << i << ' ' << n << '\n';
		cout.flush();
		cin >> pos;
		if(pos < 0) exit(0);
		if(i < pos) {
			cout << "S " << i << ' ' << pos << '\n';
			cout.flush();
			cin >> pos;
			if(pos < 0) exit(0);
		}
	}
	cout << "D\n";
	cout.flush();
	int ans;
	cin >> ans;
	if(ans == -1) exit(0);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t >> n;
	while(t--) solve();
	return 0;
}