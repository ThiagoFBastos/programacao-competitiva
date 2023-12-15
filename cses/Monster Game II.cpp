#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
struct LiChao {
	vector<pair<i64, i64>> st;
	vector<int> coords;
 
	LiChao(int l, int r) {
		coords.resize(r - l + 1);
		iota(all(coords), l);
		st.resize(4 * coords.size());
	}
 
	LiChao(vector<int>& c) : coords {c} {
		sort(all(coords));
		coords.resize(unique(all(coords)) - coords.begin());
		st.resize(4 * coords.size());
	}
 
	void fill(pair<i64, i64> x) {
		std :: fill(all(st), x);
	}
 
	i64 eval(pair<i64, i64> f, int x) {
		return x * f.fi + f.sc;
	}
 
	void add(pair<i64, i64> f) {
		add(f, 0, (int)coords.size() - 1);
	}
 
	void add(pair<i64, i64> f, int l, int r, int p = 1) {
		int m = (l + r) / 2;
 
		bool v1 = eval(f, coords[l]) < eval(st[p], coords[l]);
		bool v2 = eval(f, coords[m]) < eval(st[p], coords[m]);
 
		if(v2) swap(f, st[p]);
 
		if(l == r) return;
		else if(v1 != v2) add(f, l, m, 2 * p);
		else add(f, m + 1, r, 2 * p + 1);
	}
 
	i64 query(int x) {
		return query(x, 0, (int)coords.size() -1);
	}
 
	i64 query(int x, int l, int r, int p = 1) {
		i64 y = eval(st[p], x);
		if(l == r) return y;
		int m = (l + r) / 2;
		return min(y, x <= coords[m] ? query(x, l, m, 2 * p) : query(x, m + 1, r, 2 * p + 1));
	}
};
 
void solve() {
	int n, x;
 
	cin >> n >> x;
 
	vector<int> s(n), f(n);
	vector<i64> dp(n);
 
	for(int& v : s) cin >> v;
	for(int& v : f) cin >> v;
 
	LiChao cht(s);
 
	cht.fill(make_pair(x, 0));
 
	for(int i = 0; i < n; ++i) {
		dp[i] = cht.query(s[i]);
		cht.add(make_pair(f[i], dp[i]));
	}
 
	cout << dp.back() << '\n';
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}
