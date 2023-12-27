#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

void solve() {
	int n;
	string s;
	cin >> n >> s;
	
	if(s.front() != s.back()) {
		cout << 1 << endl;
		return;
	}
	
	for(int i = 1; i < n - 2; ++i) {
		if(s[0] != s[i] && s[0] != s[i + 1]) {
			cout << 2 << endl;
			return;
		}
	}
	
	cout << -1 << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
