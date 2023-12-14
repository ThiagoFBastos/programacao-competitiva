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
 
int l(int a, int b) {
	int k = 0;
	while(a || b) {
		if(a < b) swap(a, b);
		a -= b + 1;
		++k;
		if(a < 0) return INF;
	}
	return k;
}
	
void solve() {
 
	int n;
 
	cin >> n;
 
	auto ans = make_tuple(INF, INF, INF);
 
	for(int a = 0; a <= n; ++a)
		ans = min(ans, make_tuple(l(a, n - a), a, n - a));
	
	auto [_, _0, _1] = ans;
 
	string s;
 
	while(_0 || _1) {
		if(_0 < _1) {
			_1 -= _0 + 1;
			s += '1';
		} else {
			_0 -= _1 + 1;
			s += '0';
		}
	}
 
	cout << s << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
