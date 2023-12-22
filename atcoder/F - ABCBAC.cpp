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
	int n;
	string s;

	cin >> n >> s;

	string p = s.substr(0, n);

	if(p + string(rall(p)) == s) {
		cout << p << '\n';
		cout << n << '\n';
		return;
	}

	string a = s + "#" + string(rall(s));
	string b = string(rall(s)) + "#" + s;

	auto za = z_function(a);
	auto zb = z_function(b);

	for(int i = 1; i < n; ++i) {
		int l = i, r = 2 * n - (n - i) - 1;

		int k1 = (2 * n - r - 1) + (2 * n + 1); 
		int k2 = l + (2 * n + 1);

		if(za[k1] >= i && zb[k2] >= n - i) {
			p = s.substr(i, n);
			cout << string(rall(p)) << '\n';
			cout << i << '\n';
			return;
		}
	}

	cout << "-1\n";
}		

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
