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
 
const int N = 1e6 + 10;
int n, l;
ii pt[N];
 
bool evaluate(double d) {
	double last = 0;
	for(int i = 0; i < n; ++i) {
		auto [x, y] = pt[i];
		if(abs(y) > d) continue;
		double z = sqrt(d * d - (i64)y * y);
		if(max(0.0, x - z) <= last) last = max(last, min(l + 0.0, x + z));
	}
	return last >= l;
}
 
void solve() {
	cin >> n >> l;
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		pt[i] = {x, y};
	}
	sort(pt, pt + n);
	double lo = 0, hi = 2 * INF;	
	for(int i = 0; i < 45; ++i) {
		double m = (lo + hi) / 2;
		if(evaluate(m)) hi = m;
		else lo = m;
	}
	cout << fixed << setprecision(9) << hi << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
