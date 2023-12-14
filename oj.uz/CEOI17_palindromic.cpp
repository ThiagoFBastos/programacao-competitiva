#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
struct SuffixArray {
 
	vector<int> sa, table;
	vector<vector<int>> sp;
 
	int mod_sum(int x, int n) {
		return x >= n ? x - n : x;
	}
 
	void suffix_array(string& s) {
		s += "$";
		
		int n = s.size();
 
		vector<int> tmpSA(n), tmpOrd(n), ord(n), cnt(max(128, n));
		
		sa.resize(n);
 
		fill(cnt.begin(), cnt.begin() + 128, 0);
 
		for(char ch : s) ++cnt[ch];
		for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; ++i) sa[--cnt[s[i]]] = i;
 
		ord[sa[0]] = 0;
		
		for(int i = 1; i < n; ++i) {
			int pre = sa[i - 1], cur = sa[i];
			ord[cur] = ord[pre] + (s[cur] != s[pre]);
		}
		
		int m = ord[sa[n - 1]] + 1;
		
		for(int l = 0; (1 << l) < n; ++l) {
			fill(cnt.begin(), cnt.begin() + m, 0);
			
			for(int i = 0; i < n; ++i) ++cnt[ord[i]];
			for(int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];
			
			for(int i = n - 1; i >= 0; --i) {
				int j = mod_sum(sa[i] - (1 << l) + n, n);
				tmpSA[--cnt[ord[j]]] = j;
			}
			
			tmpOrd[tmpSA[0]] = 0;
			
			for(int i = 1; i < n; ++i) {
				int pre = tmpSA[i - 1], cur = tmpSA[i];
				auto x = make_pair(ord[pre], ord[mod_sum(pre + (1 << l), n)]);
				auto y = make_pair(ord[cur], ord[mod_sum(cur + (1 << l), n)]);
				tmpOrd[cur] = tmpOrd[pre] + (x != y);
			}
 
			swap(sa, tmpSA);
			swap(ord, tmpOrd);
 
			m = ord[sa[n - 1]] + 1;
		}
		
		s.pop_back();
		sa.erase(sa.begin());
	}
 
	int lcp(int i, int j) {
		int l = table[i], r = table[j];
		if(l > r) swap(l, r);
		if(++l > r) return (int)sa.size() - j;
		int k = 31 - __builtin_clz(r - l + 1);
		return min(sp[k][l], sp[k][r - (1 << k) + 1]);
	}
 
	void LCP(string& s) {
		int n = s.size(), match = 0;
		int l = 32 - __builtin_clz(n);
 
		suffix_array(s);
		sp.resize(l);
		table.resize(n);
 
		for(int i = 0; i < l; ++i) sp[i].resize(n);
 
		for(int i = 0; i < n; ++i) table[sa[i]] = i;
		
		for(int i = 0; i < n; ++i) {
			if(table[i]) {
				int k = i + match, j = sa[table[i] - 1] + match;
				while(k < n && j < n && s[k] == s[j]) ++k, ++j;
				match = k - i;
			}
			sp[0][table[i]] = match;
			match = max(0, match - 1);
		}
 
		for(int i = 1; i < l; ++i)
		for(int j = 0; j + (1 << i) <= n; ++j)
			sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << (i - 1))]);
	}
};
 
void solve() {
	string s;
 
	cin >> s;
 
	int n = s.size();
 
	SuffixArray sa;
 
	sa.LCP(s);
 
	int lo = 0, hi = n - 1, ans = 0;
 
	while(lo <= hi) {
		int l = min(sa.lcp(lo, hi), n - hi);
		if(lo != hi) l = min(l, hi - lo);
		if(l == n - hi) {
			ans += lo == hi ? 1 : 2;
			lo += l;
			--hi;
			n -= l;
		} else --hi;
	}
 
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
