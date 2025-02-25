#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

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
	string s;
	int n, q;
	cin >> s >> q;
	n = s.size();
	vector<int> cnt(n + 1, 0);
	auto z = z_function(s);
	for(int i = 1; i < n; ++i) ++cnt[0], --cnt[z[i] + 1];
	for(int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
	while(q--) {
		int k;
		cin >> k;
		if(k > n) cout << "0 ";
		else cout << 1 + cnt[k] << ' ';
	}
	cout << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
