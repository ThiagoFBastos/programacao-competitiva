#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

void solve() {	

	int n, m;

	cin >> n >> m;

	
	set<int> S {n};
	map<int, vector<int>> G;

	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
	}

	if(!G.count(2 * n)) {
		G[2 * n].push_back(-2);
		G[2 * n].push_back(2 * n + 2);
	}

	for(auto& [x, v] : G) {
		
		vector<int> z;

		sort(v.begin(), v.end());

		for(auto y : v) {
			if(S.count(y - 1)) z.push_back(y);
			if(S.count(y + 1)) z.push_back(y);
		}

		for(auto y : v) S.erase(y);
		for(auto y : z) S.insert(y);
	}
	
	cout << S.size() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}

