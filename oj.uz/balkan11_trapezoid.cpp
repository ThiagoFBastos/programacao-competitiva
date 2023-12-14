#include "bits/stdc++.h"
 
using namespace std;
 
#define INF    1000000000
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
using i128 = __int128;
 
const int MOD = 30013;
 
ii op(ii a, ii b) {
	if(a.fi != b.fi) return max(a, b);
	a.sc += b.sc;
	if(a.sc >= MOD) a.sc -= MOD;
	return a;
}
 
struct BIT2D {
	vector<vector<int>> Y;
	vector<int> X;
	vector<vector<ii>> bit;
 
	BIT2D() {}
 
	BIT2D(vector<ii> p) {
		for(auto [i, j] : p) X.pb(i);
		sort(all(X));
		X.resize(unique(all(X)) - X.begin());
		Y.resize(X.size() + 1);
		sort(all(p), [](auto a, auto b) {return a.sc < b.sc;});
		for(auto [i, j] : p) {
			for(int k = findPos(X, i); k < (int)Y.size(); k += k & -k)
				if(Y[k].empty() || Y[k].back() != j) Y[k].pb(j);
		}
 
		bit.resize(Y.size());
		for(int i = 0; i < (int)Y.size(); ++i) bit[i].assign(Y[i].size() + 1, ii(0, 0));
	}
 
	int findPos(vector<int>& coords, int v) {
		return upper_bound(all(coords), v) - coords.begin();
	}
 
	void upd(int i, int j, ii v) {
		for(int x = findPos(X, i); x < (int)bit.size(); x += x & -x)
			for(int y = findPos(Y[x], j); y < (int)bit[x].size(); y += y & -y)
				bit[x][y] = op(bit[x][y], v);
	}
 
	ii query(int i, int j) {
		ii ans = {0, 1};
		for(int x = findPos(X, i); x > 0; x -= x & -x)
			for(int y = findPos(Y[x], j); y > 0; y -= y & -y)
				ans = op(ans, bit[x][y]);
		return ans;
	}
};
 
void solve() {
	int n;
 
	cin >> n;
 
	vector<tuple<int, int, int, int>> t(n);
	vector<ii> query;
 
	for(auto& [a, b, c, d] : t) {
		cin >> a >> b >> c >> d;
		query.pb({b, d});
	}
 
	sort(all(t), [](auto p, auto q) {
		return min(get<0>(p), get<1>(p)) < min(get<0>(q), get<1>(q));
	});
 
	BIT2D bit(query);
	ii ans {};
 
	for(auto [a, b, c, d] : t) {
		auto [dp, cnt] = bit.query(a - 1, c - 1);
		++dp;
		bit.upd(b, d, {dp, cnt});
		ans = op(ans, {dp, cnt});
	}
	
	cout << ans.fi << ' ' << ans.sc << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
