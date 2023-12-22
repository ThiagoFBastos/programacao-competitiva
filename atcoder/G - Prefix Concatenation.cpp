#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

const int INF = 1e9;

void solve() {

	string s, t;

	cin >> s >> t;

	int n = size(s), m = size(t);
	auto p = z_function(s + "#" + t);

	vector<int> dp(m + 1, INF);
	multiset<int> sweep;
	vector<vector<int>> out(m + 1);

	sweep.insert(0);
	out[0].emplace_back(0);

	for(int i = 0; i < m; ++i) {
		if(!sweep.empty()) dp[i] = min(dp[i], *sweep.begin());

		if(p[i + n + 1]) {
			sweep.insert(dp[i] + 1);
			out[i + p[i + n + 1]].push_back(dp[i] + 1);
		}

		for(int x : out[i]) sweep.erase(sweep.find(x));
	}

	if(sweep.empty() || *sweep.begin() >= INF) cout << "-1\n";
	else cout << *sweep.begin() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
