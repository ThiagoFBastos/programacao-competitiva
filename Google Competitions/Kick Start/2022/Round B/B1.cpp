#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 1e5;

int tc;

vector<i64> G;

void solve() {
	i64 n;
	int ans = 0;
	cin >> n;

	for(i64 v : G) {
		if(v > n) break;
		ans += n % v == 0;
	}

	cout << "Case #" << ++tc << ": " << ans << '\n';
}

int main() {

	for(int k = 1; k <= MAXN; ++k) {
		string a = to_string(k);
		string b = a;
		a += string(a.rbegin(), a.rend());
		b += string(b.rbegin() + 1, b.rend());
		G.push_back(stoll(a));
		G.push_back(stoll(b));
	}

	sort(G.begin(), G.end());

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}