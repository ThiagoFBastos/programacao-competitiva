#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ii = pair<int, int>;
using ld = long double;


const int N = 1e6;

int lucky(string& s) {
	int x = (int)s[0] + (int)s[1] + (int)s[2] - 3 * '0';
	x -= (int)s[3] + (int)s[4] + (int)s[5] - 3 * '0';
	return abs(x);
}

int cnt[N + 100][30];

void solve() {
	
	int n;

	cin >> n;

	for(int i = 0; i < N; ++i) {
		string s = to_string(i);
		while((int)s.size() < 6) s = "0" + s;
		for(int j = 0; j < 30; ++j) cnt[i + 1][j] = cnt[i][j];
		++cnt[i + 1][lucky(s)];
	}

	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		int l = lucky(s);
		reverse(s.begin(), s.end());
		while((int)s.size() > 1 && s.back() == '0') s.pop_back();
		reverse(s.begin(), s.end());
		int k = stoi(s), q = 0;
		for(int j = 0; j < l; ++j) q += cnt[k + 1][j];
		cout << q << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}

