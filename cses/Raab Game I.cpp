#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int t;
 
	cin >> t;
 
	while(t--) {
		int n, a, b;
 
		cin >> n >> a >> b;
 
		if(a + b > n || (!a && b) || (a && !b)) {
			cout << "NO\n";
			continue;
		}
 
		cout << "YES\n";
 
		vector<pair<int, int>> games;
 
		int draws = n - a - b;
		int wins = a + b;
 
		for(int i = n - draws + 1; i <= n; ++i) 
			games.emplace_back(i, i);
 
		for(int i = 1; i <= a + b; ++i)
			games.emplace_back(i, (a + i - 1) % wins + 1);
 
		for(auto [c1, _] : games) cout << c1 << ' ';
		cout << '\n';
		for(auto [_, c2] : games) cout << c2 << ' ';
		cout << '\n';
	}
 
	return 0;
}
