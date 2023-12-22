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

int mod_sum(int x, int n) {
	return x >= n ? x - n : x;
}

auto suffix_array(string& s) {
	s += "$";
	
	int n = size(s), m, g;
	
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
	
	for(g = 0; (1 << g) < n; ++g) {
		int Old = g & 1, New = ~g & 1;
		
		fill(cnt.begin(), cnt.begin() + m, 0);
		
		for(int i = 0; i < n; ++i) ++cnt[ord[Old][i]];
		for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
		
		for(int i = n - 1; i >= 0; --i) {
			int j = mod_sum(p[Old][i] - (1 << g) + n, n);
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
	
	g &= 1;
	s.pop_back();
	p[g].erase(p[g].begin());
	return p[g];
}

int n, lg;
string s;
vector<int> suf;
vector<i64> pre;

void dfs(int k, int lo, int hi) {
	
	if(lo > hi) return;

	pre[lo] += (k > 0) * (hi - lo + 1ll);
	pre[hi + 1] -= (k > 0) * (hi - lo + 1ll);

	while(lo <= hi && suf[lo] + k >= n) ++lo;

	if(lo == hi) {
		pre[lo] += n - suf[lo] - k;
		pre[lo + 1] -= n - suf[lo] - k;
		return;
	}

	while(lo <= hi) {
		int i = lo;

		for(int j = lg; j >= 0; --j) {
			int pos = i + (1 << j);
			if(pos <= hi && s[min(n, suf[pos] + k)] == s[suf[lo] + k]) i = pos;
		}

		dfs(k + 1, lo, i);
		lo = i + 1;
	}
}

void solve() {

	cin >> n >> s;

	lg = 31 - __builtin_clz(n);

	suf = suffix_array(s);

	s += "$";

	pre.assign(n + 1, 0);

	dfs(0, 0, n - 1);

	for(int i = 1; i < n; ++i) pre[i] += pre[i - 1];

	vector<i64> ans(n);

	for(int i = 0; i < n; ++i) ans[suf[i]] = pre[i];

	for(i64 cnt : ans) cout << cnt << '\n';	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
