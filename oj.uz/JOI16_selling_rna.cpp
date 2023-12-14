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
 
const int N = 2e6, mod = 1e9 + 9, base = 1845;
 
vector<int> h(string& s) {
	int n = s.size();
	vector<int> a(n + 1);
	i64 k = 1;
	a[0] = 0;
	for(int i = 1; i <= n; ++i) {
		int x0 = a[i - 1];
		int& x1 = a[i];
		k = k * base % mod;
		x1 = (x0 + (s[i - 1] - '0' + 1) * k) % mod;
	}
	a.erase(a.begin());
	return a;
}
 
int t[N][4], nos = 1;
vector<ii> query[N];
unordered_map<int, int> cnt;
vector<int> ans, H[N];
 
void push(string& s) {
	int i = 0;
	for(char ch : s) {
		int& k = t[i][ch - '0'];
		if(k < 0) {
			memset(t[nos], -1, sizeof(t[nos]));
			k = nos++;
		}
		i = k;
	}
	reverse(s.begin(), s.end());
	for(int y : h(s)) H[i].push_back(y);
}
 
void f(string& s) {
	string alpha = "AGCU";
	for(char& ch : s) {
		for(int i = 0; i < 4; ++i) {
			if(ch == alpha[i]) {
				ch = i + '0';
				break;
			}
		}
	}
}
 
void dfs(int u) {	
	for(auto [pos, ht] : query[u]) {
		auto it = cnt.find(ht);
		if(it == cnt.end()) continue;
		ans[pos] -= it->second;
	}
 
	for(int v = 0; v < 4; ++v) {
		int z = t[u][v];
		if(z < 0) continue;
		dfs(z);
	}
 
	for(int ht : H[u]) ++cnt[ht];
 
	for(auto [pos, ht] : query[u]) {
		auto it = cnt.find(ht);
		if(it == cnt.end()) continue;
		ans[pos] += it->second;
	}
}
 
void solve() {
	
	int n, m;
 
	cin >> n >> m;
 
	memset(t[0], -1, sizeof(t[0]));
	ans.assign(m, 0);
 
	for(int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		f(s);
		push(s);
	}
 
	for(int i = 0; i < m; ++i) {
		string a, b;
		int k = 0;
		cin >> a >> b;
		f(a);
		f(b);
		reverse(b.begin(), b.end());
		for(char ch : a) {
			if(t[k][ch - '0'] < 0) {
				k = -1;
				break;
			}
			k = t[k][ch - '0'];
		}
		if(k < 0) continue;
		query[k].emplace_back(i, h(b).back());
	}
 
	dfs(0);
 
	for(int k : ans) cout << k << '\n';
}
 
int main() {
	int t = 1;
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	// cin >> t;
	while(t--) solve();
}
