#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MOD = 1000000001;

template<typename T>
T modMul(T a, T b, T m) {
	return T((__int128)a * b % m);
}

template<typename T>
T modMulExp(T a , T b , T m) {
	if(b == 0) return (T) 1;
	T c = modMulExp(a , b / 2, m);
	c = modMul(c, c, m) ;
	if(b % 2 != 0) c = modMul(c, a, m) ;
	return c;
}

bool miller(long long n) {
	const int pn = 9 ;
	const int p[ ] = { 2 , 3 , 5 , 7 , 11 , 13 , 17 , 19 , 23 } ;
	for(int i = 0 ; i < pn ; i++)
	if(n % p[i] == 0) return n == p[i];
	if(n < p[pn - 1]) return false;
	long long s = 0 , t = n - 1;
	while(~t & 1) t >>= 1 , ++s;
	for(int i = 0; i < pn ; ++i) {
		long long pt = modMulExp((long long)p[i], t, n);
		if(pt == 1) continue ;
		bool ok = false;
		for(int j = 0; j < s && !ok ; j++) {
			if(pt == n - 1) ok = true ;
			pt = modMul ( pt , pt , n ) ;
		}
		if(!ok) return false;
	}
	return true ;
}

template<typename T>
T pollard(T n) {
	int i = 0, k = 2 , d ;
	T x = 3, y = 3;
	while(++i) {
		x = (modMul(x, x, n) + n - 1) % n ;
		d = gcd(abs(y - x), n);
		if(d != 1 && d != n) return d;
		if(i == k) y = x, k *= 2;
	}	
	return n;
}

vector<pair<i64,int>> decomp(i64 x) {	
	vector<pair<i64,int>> a;
	if(x <= 63211236) {	
		for(int p = 2; p * p <= x; ++p) {
			if(x % p) continue;
			int i = 0;
			while(x % p == 0) x /= p, ++i;
			a.emplace_back(p, i);
		}
	} else {
		while(x > 1 && !miller(x)) {
			i64 p = pollard(x);
			int i = 0;
			while(x % p == 0) ++i, x /= p;
			a.emplace_back(p, i);
		}	
	}
	if(x > 1) a.emplace_back(x, 1);	
	return a;
}

void solve() {
	int n;

	cin >> n;

	vector<i64> a(n);

	for(i64& v : a) cin >> v;

	map<i64, vector<int>> pw;

	for(auto v : a)
		for(auto [p, k] : decomp(v))
			pw[p].push_back(k);

	int ans = 1;

	for(auto& [p, v] : pw) {
		v.push_back(0);
		sort(v.begin(), v.end());
		int m = v.size();
		for(int i = 0; i < v[m - 1] - v[m - 2]; ++i) ans = p % MOD * ans % MOD;
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
 s
