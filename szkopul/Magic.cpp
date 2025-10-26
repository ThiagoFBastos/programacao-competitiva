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

const int mod = 1e9 + 7;

void solve() {

	int n, k, ans = 0;
	string s;

	cin >> n >> s;
	
	vector<char> alpha;
	vector<int> S(n);

	for(char ch : s) alpha.push_back(ch);

	sort(alpha.begin(), alpha.end());	
	alpha.resize(unique(alpha.begin(), alpha.end()) - alpha.begin());

	for(int i = 0; i < n; ++i) S[i] = lower_bound(alpha.begin(), alpha.end(), s[i]) - alpha.begin();

	k = alpha.size();

	vector<vector<int>> f(n + 1);
	f[0].assign(k, 0);

	for(int i = 1; i <= n; ++i) {
		f[i] = f[i - 1];
		++f[i][S[i - 1]];
	}

	for(int i = 0; i < k; ++i) {
		map<vector<int>, int> cnt;
		cnt[f[0]] = 1;
		for(int j = i + 1; j <= n; j += k) {
			auto p = f[j];
			for(int i = 0; i < k; ++i) p[i] = k * p[i] - j;
			ans += cnt[p]++;
			if(ans >= mod) ans -= mod;
			if(cnt[p] >= mod) cnt[p] -= mod;
		}
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
