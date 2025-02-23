#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

vector<int> kmp(vector<int>& s) {
	int n = s.size();
	vector<int> p(n);
	p[0] = 0;
	for(int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while(j && s[i] != s[j]) j = p[j - 1];
		p[i] = j;
		if(s[i] == s[j]) ++p[i];
	}
	return p;
}

void solve() {
	int n, k, alpha;

	cin >> n >> k >> alpha;

	vector<int> s(n), t(k);

	for(int& v : s) cin >> v;
	for(int& v : t) cin >> v;

	auto p = t;
	sort(p.begin(), p.end());
	p.resize(unique(p.begin(), p.end()) - p.begin());

	for(int& v : t) v = lower_bound(p.begin(), p.end(), v) - p.begin() + 1;

	vector<int> fi(alpha + 1, -1);
	vector<vector<int>> L(alpha + 1);
	vector<array<bool, 26>> match(n);

	for(int i = 0; i < k; ++i) {
		L[t[i]].push_back(i);
		if(fi[t[i]] < 0) fi[t[i]] = i;
	}

	for(int i = 1; i <= alpha; ++i) {
		int n = L[i].size();
		if(!n) continue;
		for(int j = n - 1; j; --j) L[i][j] -= L[i][j - 1];
		L[i].erase(L[i].begin());
	}

	for(int i = 1; i <= alpha; ++i) {
		vector<int> pos, diff;
	
		for(int j = 0; j < n; ++j) {
			if(s[j] == i) {
				pos.push_back(j);
				diff.push_back(j);
				match[j].fill(false);
			}
		}

		int m = pos.size();

		if(!m) continue;

		for(int j = m - 1; j > 0; --j) diff[j] -= diff[j - 1];
		diff.erase(diff.begin());

		for(int l = 1; l <= alpha; ++l) {
			vector<int> pat;

			int n = L[l].size();

			if(!n) {
				for(int k : pos) match[k][l] = true;
				continue;
			}

			pat.reserve(n + pos.size());

			for(int v : L[l]) pat.push_back(v);

			pat.push_back(-1);

			for(int v : diff) pat.push_back(v);

			auto k = kmp(pat);

			for(int j = n + 1; j < (int)k.size(); ++j) {
				if(k[j] != n) continue;
				int lo = j - 2 * n;
				match[pos[lo]][l] = true;
			}
		}
	}

	vector<int> st_pos;

	for(int i = 0; i <= n - k; ++i) {
		vector<int> S;

		for(int j : fi) if(j != -1) S.push_back(s[j + i]);
		
		if(!is_sorted(S.begin(), S.end())) continue;
		
		auto l = S.size();

		S.resize(unique(S.begin(), S.end()) - S.begin());

		if(S.size() < l) continue;

		bool eq = true;
		for(int j = 1; j <= alpha; ++j) eq = eq && (fi[j] < 0 || match[fi[j] + i][j]);

		if(eq) st_pos.push_back(i + 1);
	}

	cout << st_pos.size() << '\n';
	for(int i : st_pos) cout << i << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 