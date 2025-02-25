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
 
double intersection(i64 a0, i64 b0, i64 a1, i64 b1) {
	return (b1 - b0) / double(a0 - a1);
}

void solve() {

/*
	(1, 100), (15, 15), (20, 5) (100, 1)
	
	xi <= x(i + 1)
	yi > y(i + 1)

	. sempre compra continuo
		valor da compra = x(r) * y(l)

	dp(i) = min j < i, dp(j) + y(j) * x(i)
*/
	int n;
	
	cin >> n;

	vector<ii> pt(n);
	int lo = 1;

	for(ii& p : pt) cin >> p.fi >> p.sc;

	sort(all(pt));

	for(int i = 1; i < n; ++i) {
		while(lo > 0 && pt[lo - 1].sc <= pt[i].sc) --lo;
		pt[lo++] = pt[i];
	}

	n = lo;
	pt.resize(n);

	vector<i64> dp(n + 1, 0);
	deque<pair<i64, i64>> st;

	for(int i = 0; i < n; ++i) {

		while((int)st.size() > 1) {
			auto a0 = *(st.end() - 1);
			auto a1 = *(st.end() - 2);
			if(intersection(pt[i].sc, dp[i], a0.fi, a0.sc) > intersection(a0.fi, a0.sc, a1.fi, a1.sc)) break;
			st.pop_back();
		}

		st.pb({pt[i].sc, dp[i]});

		while((int)st.size() > 1) {
			i64 a0 = st[0].fi, b0 = st[0].sc;
			i64 a1 = st[1].fi, b1 = st[1].sc;
			if(a0 * pt[i].fi + b0 <= a1 * pt[i].fi + b1) break;
			st.pop_front();  
		}

		dp[i + 1] = st.front().fi * pt[i].fi + st.front().sc;
	}

	cout << dp.back() << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 //	cin >> t;
    while(t--) solve();
    return 0;
}