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

typedef complex<double> base;

void fft(vector<base>& a, bool invert) {
	int n = a.size();
	
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w(1);
			for(int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	for(int i = 0; invert && i < n; ++i)
		a[i] /= n;
}

vector<base> convolution(vector<base>& a, vector<base>& b) {
	int n = 1 << (33 - __builtin_clz(a.size() + b.size()));
	a.resize(n);
	b.resize(n);
	fft(a, false);
	fft(b, false);
	vector<base> res(n);
	for(int i = 0; i < n; ++i) res[i] = a[i] * b[i];
	fft(res, true);
	return res;
}

void solve() {
	
	int n, m;

	while(cin >> n) {
		vector<int> k(n);
		int mx = 0, ans = 0;

		for(int& v : k) {
			cin >> v;
			mx = max(mx, v);
		}

		vector<base> P(mx+1), Q(mx+1);

		P[0] = 1;
		for(int v : k) P[v] = Q[v] = 1;

		auto R = convolution(P, Q);

		cin >> m;

		while(m--) {
			int d;
			cin >> d;
			ans += d < (int)R.size() && (int)round(R[d].real()) != 0;
		}

		cout << ans << '\n';
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