#include "bits/stdc++.h"
using namespace std;

auto kmp(string& a, string& b) {
	string s = a + "@" + b;
	int n = size(s);
	vector<int> p(n), q;
	p[0] = 0;
	for(int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while(j && s[i] != s[j]) j = p[j - 1];
		p[i] = j + (s[i] == s[j]);	
	}
	int m = size(a) + 1;
	for(int i = m; i < n; ++i) q.push_back(p[i]);
	return q;
}

const int N = 2e5;

int bit[30][2][N];

void dfs(int x, int y, int z) {
	if(!y) {
		cout << x << ' ' << z << '\n';
		return;
	}
	if(bit[y - 1][0][x]) dfs(x, y - 1, 2 * z);
	if(bit[y - 1][1][x]) dfs(x, y - 1, 2 * z + 1);
}

void solve() {
	int n;
	cin >> n;
	
	vector<int> a(n), b(n);
	
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 0; i < n; ++i) cin >> b[i];
	
	for(int i = 0; i < 30; ++i) {
		string s;
		for(int j = 0; j < n; ++j) s += ((b[j] & 1 << i) != 0) + '0';
		for(int k = 0; k < 2; ++k) {
			string t;
			for(int j = 0; j < n; ++j) t += (((a[j] ^ k << i) & 1 << i) != 0) + '0';
			t += t;
			auto c = kmp(s, t);
			for(int j = 0; j < n; ++j) bit[i][k][j] = c[j + n - 1] == n;
		}
	}
	
	for(int i = 0; i < n; ++i) {
		int cnt = 0;
		for(int j = 0; j < 30; ++j) cnt += bit[j][0][i] || bit[j][1][i];
		if(cnt != 30) continue;
		dfs(i, 30, 0);
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
