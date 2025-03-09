#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

int mod_sum(int x, int n) {
	if(x < 0) return x + n;
	else if(x >= n) return x - n;
	return x;
}

auto suffix_array(string& s) {
	s += "$";
	
	int n = size(s), m, g;
	
	vector<int> p[2], ord[2], cnt(1 + max(n, 128));
	
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
	
	for(g = 0; (1 << g) < n; ++g) {
		int Old = g & 1, New = ~g & 1;
		
		fill(cnt.begin(), cnt.begin() + m, 0);
		
		for(int i = 0; i < n; ++i) ++cnt[ord[Old][i]];
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		
		for(int i = n - 1; i >= 0; --i) {
			int j = mod_sum(p[Old][i] - (1 << g), n);
			p[New][--cnt[ord[Old][j]]] = j;
		}
		
		ord[New][p[New][0]] = 0;
		
		for(int i = 1; i < n; ++i) {
			int pre = p[New][i - 1], cur = p[New][i];
			auto x = make_pair(ord[Old][pre], ord[Old][mod_sum(pre + (1 << g), n)]);
			auto y = make_pair(ord[Old][cur], ord[Old][mod_sum(cur + (1 << g), n)]);
			ord[New][cur] = ord[New][pre] + (x != y);
		}
		m = ord[New][p[New].back()] + 1;
	}
	
	if(n >= 2) g = (g - 1) & 1;
	
	s.pop_back();
	p[g].erase(p[g].begin());
	
	return p[g];
}

auto LCP(vector<int>& suffix, string& s) {	
	int n = s.size(), match = 0;
	vector<int> table(n), lcp(n);
	
	for(int i = 0; i < n; ++i) table[suffix[i]] = i;
	
	for(int i = 0; i < n; ++i) {
		if(table[i]) {
			int k = i + match, j = suffix[table[i] - 1] + match;
			while(k < n && j < n && s[k] == s[j]) ++k, ++j;
			match = k - i;
		}
		lcp[i] = match;
		match = max(0, match - 1);
	}
	
	return lcp;
}

void solve() {				
	string s;
	
	cin >> s;
	
	if(s == "*") exit(0);
	
	int n = size(s);
	auto sufixo = suffix_array(s);
	auto lcp = LCP(sufixo, s);
	vector<int> ptr(n, 0);
	i64 cnt = 0;
	
	ptr[0] = 0;
	
	for(int i = 1; i < n; ++i) {
		int k = sufixo[i];
		cnt += max(0, lcp[k] - ptr[i - 1]);
		ptr[i] = lcp[k];
	}
	
	cout << cnt << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(true) solve();
 	return 0;
}