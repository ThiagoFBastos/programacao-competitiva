#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2,sse3")
#include "bits/stdc++.h"
 
using namespace std;
 
int n, pw[2], mod[2];
string s;
vector<int> h[2], p[2];
 
void build();
int query(int l, int r, int k);
bool cmp(int a, int b, int c, int d);
 
void build() {
	n = s.size();
	pw[0] = 26;
	pw[1] = 37;
	mod[0] = 1e9 + 7;
	mod[1] = 1e9 + 9;
	for(int i = 0; i < 2; ++i) {
		h[i].resize(n + 1);
		p[i].resize(n + 1);
		h[i][0] = 0;
		p[i][0] = 1;
		for(int k = 1; k <= n; ++k) {
			p[i][k] = 1LL * pw[i] * p[i][k - 1] % mod[i];
			h[i][k] = (h[i][k - 1] + p[i][k] * (s[k - 1] - 'a' + 0LL)) % mod[i];
		}
	}
}
 
int query(int l, int r, int k) {
	int hash = p[k][n - l - 1] * (h[k][r + 1] - h[k][l] + 0LL) % mod[k];
	return hash < 0 ? hash + mod[k] : hash;
}
 
bool cmp(int a, int b, int c, int d) {
	return query(a, b, 0) == query(c, d, 0) && query(a, b, 1) == query(c, d, 1);
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	build();
	vector<int> p;
	for(int k = 1; k <= n; ++k) {
		int j = n / k, i = n % k;
		if((j == 1 || cmp(0, k * (j - 1) - 1, k, n - i - 1)) && (i == 0 || cmp(0, i - 1, n - i, n - 1)))
			p.push_back(k);
	}
	for(int x : p) cout << x << ' ';
	cout << '\n';
	return 0;
}
