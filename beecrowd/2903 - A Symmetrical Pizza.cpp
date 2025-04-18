#include <bits/stdc++.h>

using namespace std;

void solve() {
	string x;
	int delta = 0;
	cin >> x;
	for(char ch : x) if(ch != '.') delta = 10 * delta + ch - '0';
	delta = min(delta, 36000 - delta);
	cout << 36000 / gcd(delta, 36000 % delta)  << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}