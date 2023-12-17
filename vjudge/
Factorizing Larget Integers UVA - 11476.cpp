#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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


i64 modMul(i64 a, i64 b, i64 m) {
	return (i64)((__int128)a * b % m);
}

i64 modMulExp(i64 a, i64 p, i64 m) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = modMul(ans, a, m);
		a = modMul(a, a, m);
	}
	return ans;
}

bool miller(i64 n) {
	const int pn = 9;
	const int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	for(int k : p)
		if(n % k == 0)
			return n == k;
	if(n < p[pn - 1]) return false;
	i64 t = n - 1;
	int s = 0;
	while(~t & 1) t >>= 1, ++s;
	for(int k : p) {
		i64 pt = modMulExp(k, t, n);
		if(pt == 1) continue;
		bool ok = false;
		for(int j = 0; j < s && !ok; ++j) {
			ok = ok || pt == n - 1;
			pt = modMul(pt, pt, n);
		}
		if(!ok) return false;
	}
	return true;
}

i64 rho(i64 n) {
	if (n == 1 or miller(n)) return n;
	auto f = [n](i64 x) {return modMul(x, x, n) + 1;};
	i64 x = 0, y = 0, t = 30, prd = 2, x0 = 1, q;
	while (t % 40 != 0 or __gcd(prd, n) == 1) {
		if (x==y) x = ++x0, y = f(x);
		q = modMul(prd, abs(x-y), n);
		if (q != 0) prd = q;
		x = f(x), y = f(f(y)), t++;
	}
	return __gcd(prd, n);
}

vector<i64> fact(i64 n) {
	if (n == 1) return {};
	if (miller(n)) return {n};
	i64 d = rho(n);
	vector<i64> l = fact(d), r = fact(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}

void solve() {
	map<i64, int> mp;
	bool first = true;
	i64 n;

	cin >> n;

	for(i64 p : fact(n)) ++mp[p];
	
	cout << n << " = ";

	for(auto& t : mp) {
		if(!first) cout << " * ";
		first = false;
		cout << t.fi;
		if(t.sc > 1) cout << '^' << t.sc;
	}

	cout << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
