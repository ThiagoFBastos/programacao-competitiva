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
using i128 = __int128;

istream& operator>>(istream& is, i128& n) {
	string s;
	is >> s;
	n = 0;
	for(char c : s) n = 10 * n + c - '0';
	return is;
}

ostream& operator<<(ostream& os, i128 n) {
	string s;
	if(!n) s = "0";
	for(; n > 0; n /= 10) s += n % 10 + '0';
	reverse(all(s));
	os << s;
	return os;
}

i128 gcd(i128 a, i64 b) {
	return b == 0 ? a : gcd(b, a % b);
}

namespace factorization {

	template<class T>
	T modMul(T a, T b, T m) {
		return (T)((__int128)a * b % m);
	}

	template<class T>
	T modMulExp(T a, T p, T m) {
		T ans = 1;
		for(; p > 0; p >>= 1) {
			if(p & 1) ans = modMul(ans, a, m);
			a = modMul(a, a, m);
		}
		return ans;
	}

	template<class T>
	bool miller(T n) {
		const int pn = 9;
		const T p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

		for(T k : p)
			if(n % k == 0)
				return n == k;
		
		if(n < p[pn - 1]) return false;

		T t = n - 1;
		int s = 0;

		while(~t & 1) t >>= 1, ++s;

		for(T k : p) {
			T pt = modMulExp(k, t, n);

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

	template<class T>
	T f(T x, T c, T mod) {
		return (modMul(x, x, mod) + c) % mod;
	}

	template<class T>
	T rho(T n) {
		mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
		T x, y, g = n;
		while(g == n) {
			T x0 = rnd(), c = rnd();
			x = y = x0;
			g = 1;
			while(g == 1) {
				x = f(x, c, n);
				y = f(y, c, n);
				y = f(y, c, n);
				g = gcd(x < y ? y - x : x - y, n);
			}
		}
		return g;
	}
	
	template<class T>
	vector<pair<T, int>> factorize(T n) {	
		vector<pair<T, int>> f;
		for(T p = 2; p * p * p * p <= n; ++p) {
			if(n % p) continue;
			int i = 0;
			while(n % p == 0) n /= p, ++i;
			f.pb({p, i});
		}
		while(n != 1) {
			if(miller(n)) {
				f.pb({n, 1});
				break;
			}
			T p[2] = {rho(n), 0};
			if(!miller(p[0])) {
				p[1] = rho(p[0]);
				p[0] /= p[1];
			}
			for(T k : p) {
				if(!k) break;
				int i = 0;
				while(n % k == 0) n /= k, ++i;
				f.pb({k, i});
			}
		}
		return f;
	}
};

void solve() {
	while(true) {
		i128 n;

		cin >> n;

		if(!n) break;
		else if(n == 1) {cout << "1^1\n"; continue;}

		auto f = factorization :: factorize(n);

		sort(all(f));

		cout << f[0].fi << '^' << f[0].sc;
		for(int i = 1; i < (int)f.size(); ++i) cout << ' ' << f[i].fi << '^' << f[i].sc;
		cout << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}