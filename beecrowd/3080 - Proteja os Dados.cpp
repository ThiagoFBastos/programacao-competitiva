#include "bits/stdc++.h"
using namespace std;
int mod_sum(int a, int b) {
	return a >= b ? a - b : a;
}
vector<int> suffix_array(string& s) {
	s += '\n';
	int n = size(s);
	vector<int> p[2], v[2], cnt(max(128, n) + 1, 0);
	for(int k = 0; k < 2; ++k) {
		p[k].resize(n);
		v[k].resize(n);
	}
	for(char ch : s) ++cnt[ch + 1];
	for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i) p[0][cnt[s[i]]++] = i;
	v[0][p[0][0]] = 0;
	for(int i = 1; i < n; ++i) v[0][p[0][i]] = (s[p[0][i]] != s[p[0][i - 1]]) + v[0][p[0][i - 1]];
	for(int l = 1; l < n; l <<= 1) {
		fill(cnt.begin(), cnt.end(), 0);
		for(int	i = 0; i < n; ++i) ++cnt[v[0][i] + 1];
		for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; ++i) {
			int k = mod_sum(p[0][i] - l + n, n);
			p[1][cnt[v[0][k]]++] = k;
		}
		v[1][p[1][0]] = 0;
		for(int i = 1; i < n; ++i) {
			int k = p[1][i - 1], j = p[1][i];
			pair a = {v[0][k], v[0][mod_sum(k + l, n)]};
			pair b = {v[0][j], v[0][mod_sum(j + l, n)]};
			v[1][j] = (a != b) + v[1][k];
		}
		for(int i = 0; i < n; ++i) {
			v[0][i] = v[1][i];
			p[0][i] = p[1][i];
		}
	}
	s.pop_back();
	p[0].erase(p[0].begin());
	return p[0];
}
struct sparse_table {
	vector<vector<int>> sp;
	sparse_table(vector<int>& a) {
		int n = size(a);
		int m = 32 - __builtin_clz(n);
		sp = vector<vector<int>>(m, vector<int>(n, 0));
		for(int i = 0; i < n; ++i) sp[0][i] = a[i];
		for(int i = 1; i < m; ++i)
		for(int j = 0; j + (1 << i) - 1 < n; ++j)
			sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << i - 1)]);
	}
	int query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return min(sp[k][l], sp[k][r - (1 << k) + 1]);
	}
};
void solve() {
	string s;
	int cnt, n;
	getline(cin, s);
	cin >> cnt;
	if(cnt == 1) {
		cout << s << '\n';
		return;
	}
	n = size(s);
	auto suf = suffix_array(s);
	vector<int> lcp(n), pos(n), past(n);
	int k = 0;
	for(int i = 0; i < n; ++i) {
		pos[suf[i]] = i;
		past[suf[i]] = i ? suf[i - 1] : -1;
	}
	for(int i = 0; i < n; ++i) {
		if(past[i] == -1) {lcp[pos[i]] = 0; continue;}
		int j = past[i];
		while(k + i < n && k + j < n && s[k + i] == s[k + j]) ++k;
		lcp[pos[i]] = k;
		k = max(k - 1, 0);
	}
	sparse_table sp(lcp), index(suf);
	pair p = {-1, -1};
	for(int i = 0; i < n; ++i) {
		int ans;
		if(i + 1 >= cnt && (ans = sp.query(i - cnt + 2, i)) > 0) {
			int L = 1, R = i - cnt + 2;
			while(L < R) {
				int mid = (L + R) / 2;
				if(sp.query(mid, i) == ans) R = mid;
				else L = mid + 1;
			}
			p = max(p, make_pair(ans, -index.query(R - 1, i)));
		}
	}
	if(p.first == -1) cout << ":)\n";
	else cout << s.substr(-p.second, p.first) << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}