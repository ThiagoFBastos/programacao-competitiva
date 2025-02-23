#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4")

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

i64 exp(i64 n, i64 p, i64 mod) {
	i64 ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = ans * n % mod;
		n = n * n % mod;
	}
	return ans;
}

const int mod[] = {1004535809, 1092616193, 998244353};
const int root[] = {12289, 23747, 15311432};
const int root_1[] = {313564925, 642907570, 469870224};
const int root_pw[] = {1 << 21, 1 << 21, 1 << 23};

void ntt(vector<int>& a, bool invert, int m) {
	int n = a.size();

	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 2, wlen; len <= n; len <<= 1) {
		wlen = invert ? root_1[m] : root[m];

		for(int i = len; i < root_pw[m]; i <<= 1)
			wlen = (i64)wlen * wlen % mod[m];

		for(int i = 0; i < n; i += len) {
			for(int j = 0, w = 1; j < len / 2; ++j) {
				i64 u = a[i+j], v = (i64)a[i+j+len/2] * w % mod[m];
				a[i+j] = u + v >= mod[m] ? u + v - mod[m] : u + v;
				a[i+j+len/2] = u - v < 0 ? u - v + mod[m] : u - v;
				w = (i64)w * wlen % mod[m];
			}
		}
	}

	if(invert) {
		i64 x = exp(n, mod[m] - 2, mod[m]);
		for(int& y : a) y = (i64)y * x % mod[m];		
	}
}

void ntt(vector<ii>& a, int m) {
	int n = a.size();

	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);	
	}

	for(int len = 2, wlen; len <= n; len <<= 1) {
		wlen = root[m];

		for(int i = len; i < root_pw[m]; i <<= 1)
			wlen = (i64)wlen * wlen % mod[m];

		for(int i = 0; i < n; i += len) {
			for(int j = 0, w = 1; j < len / 2; ++j) {
				i64 u1 = a[i+j].fi, v1 = (i64)a[i+j+len/2].fi * w % mod[m];
				i64 u2 = a[i+j].sc, v2 = (i64)a[i+j+len/2].sc * w % mod[m];
				a[i+j].fi = u1 + v1 >= mod[m] ? u1 + v1 - mod[m] : u1 + v1;
				a[i+j+len/2].fi = u1 - v1 < 0 ? u1 - v1 + mod[m] : u1 - v1;
				a[i+j].sc = u2 + v2 >= mod[m] ? u2 + v2 - mod[m] : u2 + v2;
				a[i+j+len/2].sc = u2 - v2 < 0 ? u2 - v2 + mod[m] : u2 - v2;
				w = (i64)w * wlen % mod[m];
			}
		}
	}

	
		i64 x = exp(n, mod[m] - 2, mod[m]);
		for(int i = 0; i < n; ++i) {
			a[i].fi = a[i].fi * x % mod[m];
			a[i].sc = a[i].sc * x % mod[m];
		}	
	
}

vector<int> convolution(vector<ii>& a, int m) {
	int n = 1 << (32 - __builtin_clz(2*a.size()));
	a.resize(n);
	ntt(a, m);
	vector<int> res(n);
	for(int i = 0; i < n; ++i) res[i] = (i64)a[i].fi * a[i].sc % mod[m];	
	ntt(res, true, m);
	return res;
}

void solve() {
	string s;

	cin >> s;

	int n = size(s), sum = 0, ps = 0, ans = 0;

	for(char c : s) sum += c - 'a' + 1;

	vector<ii> p(sum+1,ii(0,0));

	p[0].fi = 1;
	p[sum].sc = 1;

	for(int i = 1; i <= n; ++i) {
		ps += s[i-1]-'a'+1;
		p[ps].fi=p[sum-ps].sc=1;
	}

	auto r = convolution(p, 2);

	for(int i = sum + 1; i < (int)r.size(); ++i) ans += !!r[i];

	cout << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 // cin >> t;
    while(t--) solve();
    return 0;
}

