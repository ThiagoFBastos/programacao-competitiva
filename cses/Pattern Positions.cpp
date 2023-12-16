#include "bits/stdc++.h"
using namespace std;
struct sparse_table {
	vector<vector<int>> sp;
	sparse_table(vector<int>& arr) {
		int n = size(arr);
		int m = 32 - __builtin_clz(n);
		sp = vector<vector<int>>(m, vector<int>(n));
		for(int i = 0; i < n; ++i) sp[0][i] = arr[i];
		for(int i = 1; i < m; ++i)
		for(int j = 0; j + (1 << i) - 1 < n; ++j)
			sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << i - 1)]);
	}
	int query(int l, int r) {
		int h = 31 - __builtin_clz(r - l + 1);
		return min(sp[h][l], sp[h][r - (1 << h) + 1]);
	}
};
vector<int> suffix_array(string& s) {
	s += "@";
	int n = size(s);
	vector<int> v(n), vc(n), p(n), pc(n), cnt(max(128, n) + 1, 0);
	for(char ch : s) ++cnt[ch + 1];
	for(int k = 1; k < 128; ++k) cnt[k] += cnt[k - 1];
	for(int k = 0; k < n; ++k) v[k] = cnt[s[k]];
	for(int k = 0; k < n; ++k) p[cnt[s[k]]++] = k;
	for(int m = 1; 2 * m <= n; m <<= 1) { 
		fill(cnt.begin(), cnt.end(), 0);
		for(int i = 0; i < n; ++i) ++cnt[v[(p[i] - m + n) % n] + 1];
		for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; ++i) {
			int j = (p[i] - m + n) % n;
			pc[cnt[v[j]]++] = j;
		}
		copy(pc.begin(), pc.end(), p.begin());
		vc[p[0]] = 0;
		for(int i = 1; i < n; ++i) {
			auto a = make_pair(v[p[i - 1]], v[(p[i - 1] + m) % n]);
			auto b = make_pair(v[p[i]], v[(p[i] + m) % n]);
			vc[p[i]] = (a != b) + vc[p[i - 1]];
		}
		copy(vc.begin(), vc.end(), v.begin());
	}
	s.pop_back();
	p.erase(p.begin());
	return p;
}
void solve() {
	string str;
	int n, m;
	cin >> str >> n;
	auto suf = suffix_array(str);
	m = size(str);
	str += "@";
	sparse_table sp(suf);
	for(int i = 0; i < n; ++i) {
		string pat;
		int L = 0, R = m - 1;
		cin >> pat;
		for(int i = 0; i < int(size(pat)); ++i) {
			int lo = L, hi = R;
			for(int k = 31 - __builtin_clz(R - L + 1); k >= 0; --k) {
				int l = lo + (1 << k), r = hi - (1 << k);
				if(l <= R && str[min(m, suf[l] + i)] < pat[i]) lo = l;
				if(r >= L && str[min(m, suf[r] + i)] > pat[i]) hi = r;
			}
			if(str[min(m, suf[lo] + i)] != pat[i]) ++lo;
			if(str[min(m, suf[hi] + i)] != pat[i]) --hi;
			L = lo, R = hi;
			if(L > R) break;
		}
		if(L > R) cout << "-1\n";
		else cout << 1 + sp.query(L, R) << '\n';
	}
}	
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
