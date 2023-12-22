#include "bits/stdc++.h"

using namespace std;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;
 
vector<int> z_function(string& s) {
    int n = (int) s.length();
    vector<int> z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min (r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve() {
	string s, t, tmp;

	cin >> s >> t;

	while(true) {
		tmp += s;
		if(tmp.size() > t.size()) break;
	}
	
	swap(s, tmp);

	int n = s.size(), m = t.size(), ans = 0;
	vector<int> to(n, -1), depth(n, -1);
	vector<bool> check(n, false);

	string p = t + "$" + s + s;

	auto z = z_function(p);

	for(int i = 0; i < n; ++i) {
		int k = i + m + 1;
		check[i] = z[k] == m;
	}

	for(int i = 0; i < n; ++i) if(check[i] && check[(i + m) % n]) to[i] = (i + m) % n;

	auto dfs = [&](auto& dfs, int x, int y)->bool {
		int z = to[y];
		if(z == x) return false;
		else if(z == -1) depth[y] = 1;
		else {
			if(depth[z] < 0 && !dfs(dfs, x, z)) return false;
			depth[y] = 1 + depth[z];
		}
		return true;
	};

	for(int i = 0; i < n; ++i) {
		if(!check[i]) continue;
		if(!dfs(dfs, i, i)) {
			cout << "-1\n";
			return;
		}
		ans = max(ans, depth[i]);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
