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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
i64 uniform(i64 l, i64 r) {
	uniform_int_distribution<i64> uid(l, r);
	return uid(rng);
}

template<class T, int k>
struct MersenneHash {
	static i64 P;
	const i64 mod = (1ll << k) - 1;
	vector<i64> p, h;

	MersenneHash() {}
	MersenneHash(T& s) : p(s.size() + 1), h(s.size() + 1) {
		p[0] = 1, h[0] = 0;
		for(int i = 1; i <= (int)s.size(); ++i) {
			p[i] = mulmod(p[i - 1], P);
			h[i] = addmod(h[i - 1], mulmod(p[i], s[i - 1]));
		}
	}

	inline i64 addmod(i64 a, i64 b) {
		a += b;
		return a >= mod ? a - mod : a;
	}

	inline i64 mulmodSQRT(i64 a, i64 b) {
		return addmod((a*b) & mod, (a*b) >> k);
	}
	
	inline i64 mulmod(i64 a, i64 b) {
		int m1 = (k + 1) >> 1, m2 = k >> 1;
		i64 a1 = a >> m1, a2 = a & ((1ll << m1) - 1), b1 = b >> m2, b2 = b & ((1ll << m2) - 1);
		i64 s = mulmodSQRT(a1, b1), t = mulmodSQRT(a1, b2);
		i64 u = mulmodSQRT(b1, a2), v = mulmodSQRT(a2, b2);
		t = addmod((t & ((1ll<<m2)-1)) << m1, t >> (k - m1));
		u = addmod((u & ((1ll<<m1)-1)) << m2, u >> (k - m2));
		return addmod(addmod(s, t), addmod(u, v));
	}

	i64 operator()(int l, int r) {
		int n = (int)p.size() - 1;
		return mulmod(addmod(h[r + 1] - h[l], mod), p[n - l - 1]);
	}
};

template<class T, int k>
i64 MersenneHash<T, k> :: P = uniform(256, (1ll << k) - 1);

void solve() {
	string s, type;	
	set<i64> good;
	int k;

	cin >> s >> type >> k;
	
	for(char& c : type) c ^= 1;

	int n = s.size();
	MersenneHash<string, 61>  hsh(s);

	for(int l = 0; l < n; ++l) {
		int bad = 0;
		for(int r = l; r < n && bad + type[s[r] - 'a'] - '0' <= k; ++r) {
			bad += type[s[r] - 'a'] - '0';
			good.insert(hsh(l, r));
		}
	}

	cout << good.size() << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}
