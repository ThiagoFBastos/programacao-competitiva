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
	int n;

	cin >> n;

	vector<i64> a(n);
	
	for(i64& v : a) cin >> v;
		
	if(n <= 5000) {
		vector<i64> mp(n * (n + 1) / 2);

		for(int i = 0, k = 0; i < n; ++i) {
			i64 s = 0;
			for(int j = i; j < n; ++j) {
				s += a[j];
				mp[k++] = s;
			}
		}
		
		sort(all(mp));
		mp.resize(unique(all(mp)) - mp.begin());

		cout << (int)mp.size() - 1 << '\n';
		return;
	}

	a.insert(a.begin(), 0);
	for(int i = 1; i <= n; ++i) a[i] += a[i - 1];

	vector<base> P(a[n] + 1), Q(a[n] + 1);	
	int cnt = 0;

	for(int i = 1; i <= n; ++i) P[a[i]] = Q[a[n] - a[i - 1]] = 1;
	
	auto R = convolution(P, Q);

	for(int i = a[n] + 1; i < (int)R.size(); ++i) cnt += (i64)round(R[i].real()) != 0;

	cout << cnt - 1 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}