#include <bits/stdc++.h>

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

int mod_sum(int x, int n) {
	return x >= n ? x - n : x;
}

vector<int> suffix_array(string& s) {
		
	s += "#";

	int n = s.size(), m, g;
	
	vector<int> p[2], ord[2], cnt(max(n, 128));
	
	for(int i = 0; i < 2; ++i) {
		p[i].resize(n);
		ord[i].resize(n);
	}
	
	fill(cnt.begin(), cnt.begin() + 128, 0);
	
	for(char ch : s) ++cnt[ch];
	for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i) p[0][--cnt[s[i]]] = i;

	ord[0][p[0][0]] = 0;
	
	for(int i = 1; i < n; ++i) {
		int pre = p[0][i - 1], cur = p[0][i];
		ord[0][cur] = ord[0][pre] + (s[cur] != s[pre]);
	}
	
	m = ord[0][p[0].back()] + 1;
	
	for(int g = 0; (1 << g) < n; ++g) {
		fill(cnt.begin(), cnt.begin() + m, 0);
		
		for(int i = 0; i < n; ++i) ++cnt[ord[0][i]];
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		
		for(int i = n - 1; i >= 0; --i) {
			int j = mod_sum(p[0][i] - (1 << g) + n, n);
			p[1][--cnt[ord[0][j]]] = j;
		}
		
		ord[1][p[1][0]] = 0;
		
		for(int i = 1; i < n; ++i) {
			int pre = p[1][i - 1], cur = p[1][i];
			auto x = make_pair(ord[0][pre], ord[0][mod_sum(pre + (1 << g), n)]);
			auto y = make_pair(ord[0][cur], ord[0][mod_sum(cur + (1 << g), n)]);
			ord[1][cur] = ord[1][pre] + (x != y);
		}

		swap(p[0], p[1]);
		swap(ord[0], ord[1]);
		m = ord[0][p[0].back()] + 1;
	}

	s.pop_back();
	p[0].erase(p[0].begin());
	
	return p[0];
}

vector<int> LCP(vector<int>& suffix, string& s) {	
	int n = s.size(), match = 0;
	vector<int> table(n), lcp(n);
	
	for(int i = 0; i < n; ++i) table[suffix[i]] = i;
	
	for(int i = 0; i < n; ++i) {
		if(table[i]) {
			int k = i + match, j = suffix[table[i] - 1] + match;
			while(k < n && j < n && s[k] == s[j]) ++k, ++j;
			match = k - i;
		}
		lcp[table[i]] = match;
		match = max(0, match - 1);
	}
	
	return lcp;
}

void solve() {
	int n, m;
	string s;

	cin >> n >> s;

	s = s + s;
	
	auto sa = suffix_array(s);
	auto lcp = LCP(sa, s);

	m = 2 * n;

	vector<int> table(m);

	for(int i = 0; i < m; ++i) table[sa[i]] = i;

	vector<int> P;
	i64 ans = 0;

	for(int i : sa) if(i < n) P.push_back(i);

	for(int i = 1; i < n; ++i) {
		int L = n;
		for(int j = table[P[i - 1]] + 1; j <= table[P[i]]; ++j)
			L = min(L, lcp[j]);
		ans += L;
	}
	
	cout << fixed << setprecision(9) << ans / (n - 1.0L) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}