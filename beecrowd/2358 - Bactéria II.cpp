#include "bits/stdc++.h"
using namespace std;
void destroy(string& dna, string& rna) {
	string s = rna + "#" + dna;
	int n = size(s), m = size(rna);
	vector<int> pre(n);
	pre[0] = 0;
	for(int k = 1; k <= m; ++k) {
		int j = pre[k - 1];
		while(j > 0 && s[j] != s[k]) j = pre[j - 1];
		pre[k] = (s[j] == s[k]) + j;
	}
	stack<int> st;
	st.push(m);
	for(int k = m + 1; k < n; ++k) {
		int j = pre[st.top()];
		while(j > 0 && s[j] != s[k]) j = pre[j - 1];
		pre[k] = (s[k] == s[j]) + j;
		st.push(k);
		if(pre[k] == m) for(int i = 0; i < m; ++i) st.pop();
	}
	dna = "";
	while(st.top() > m) {
		dna += s[st.top()];
		st.pop();
	}
	reverse(dna.begin(), dna.end());
}
int mod_sum(int a, int n) {
	return a >= n ? a - n : a;
}
vector<int> suffix_array(string& s) {
	int n = size(s);
	vector<int> pos[2], val[2], cnt(max(128, n) + 1, 0);
	for(int k = 0; k < 2; ++k) {
		pos[k].resize(n);
		val[k].resize(n);
	}
	for(char ch : s) ++cnt[ch + 1];
	for(int i = 1; i < 128; ++i) cnt[i] += cnt[i - 1];
	for(int i = 0; i < n; ++i) pos[0][cnt[s[i]]++] = i;
	val[0][pos[0][0]] = 0;
	for(int i = 1; i < n; ++i) val[0][pos[0][i]] = val[0][pos[0][i - 1]] + (s[pos[0][i]] != s[pos[0][i - 1]]);
	for(int l = 1; l < n; l <<= 1) {
		fill(cnt.begin(), cnt.end(), 0);
		for(int i = 0; i < n; ++i) ++cnt[val[0][i] + 1];
		for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
		for(int i = 0; i < n; ++i) {
			int k = mod_sum(pos[0][i] - l + n, n);
			pos[1][cnt[val[0][k]]++] = k;
		}
		val[1][pos[1][0]] = 0;
		for(int i = 1; i < n; ++i) {
			int a = pos[1][i - 1], b = pos[1][i];
			pair x = {val[0][a], val[0][mod_sum(a + l, n)]};
			pair y = {val[0][b], val[0][mod_sum(b + l, n)]};
			val[1][b] = (x != y) + val[1][a];
		}
		for(int i = 0; i < n; ++i) {
			pos[0][i] = pos[1][i];
			val[0][i] = val[1][i];
		}
	}
	return pos[0];
}	
using ii = pair<int, int>;
vector<vector<ii>> sp;
void create(vector<int>& lcp, vector<int>& bit) {
	int n = size(lcp), m = 32 - __builtin_clz(size(lcp));
	sp = vector<vector<ii>>(m, vector<ii>(n, make_pair(0, 0)));
	for(int i = 0; i < n; ++i) sp[0][i] = {lcp[i], bit[i]};
	for(int i = 1; i < m; ++i)
	for(int j = 0; j + (1 << i) - 1 < n; ++j) {
		pair L = sp[i - 1][j];
		pair R = sp[i - 1][j + (1 << i - 1)];
		sp[i][j] = {min(L.first, R.first), L.second | R.second};
	}
}
ii query(int l, int r) {
	int h = 31 - __builtin_clz(r - l + 1);
	pair L = sp[h][l];
	pair R = sp[h][r - (1 << h) + 1];
	return {min(L.first, R.first), L.second | R.second};
}
void solve() {
	int n, m = 0;
	cin >> n;
	if(cin.eof()) exit(0);
	vector<string> dna(n);
	string rna;
	for(int i = 0; i < n; ++i) cin >> dna[i];
	cin >> rna;
	for(string& codigo : dna) {
		destroy(codigo, rna);
		m += size(codigo) + 1;
	}
	if(n == 1) {
		cout << dna[0] << '\n';
		return;
	}
	string s;
	vector<int> bit(m, 0), bitP(m);
	for(int i = 0; i < n; ++i) {
		int k = size(s);
		s += dna[i] + char(' ' + i);
		for(int j = k; j < int(size(s)) - 1; ++j) bit[j] = 1 << i;
	}
	auto suf = suffix_array(s);
	vector<int> lcp(m), pre(m), pos(m);
	int k = 0;
	for(int i = 0; i < m; ++i) {
		bitP[i] = bit[suf[i]];
		pos[suf[i]] = i;
		pre[suf[i]] = i ? suf[i - 1] : -1;
	}
	for(int i = 0; i < m; ++i) {
		if(pre[i] == -1) {lcp[pos[i]] = 0; continue;}
		int j = pre[i];
		while(k + j < m && k + i < m && s[k + j] == s[k + i]) ++k;
		lcp[pos[i]] = k;
		k = max(0, k - 1);
	}
	create(lcp, bitP);
	auto ans = make_pair(-1, -1);
	for(int i = 1; i < m; ++i) {
		if(query(0, i).second != (1 << n) - 1) continue;
		int L = i;
		for(int k = 31 - __builtin_clz(i); k >= 0; --k) {
			int l = L - (1 << k);
			if(l < 0 || query(l, i).second == (1 << n) - 1) continue;
			L = l;
		}
		ans = max(ans, make_pair(query(L, i).first, -i));
	}
	cout << s.substr(suf[-ans.second], ans.first) << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	for(;;) solve();
	return 0;
}