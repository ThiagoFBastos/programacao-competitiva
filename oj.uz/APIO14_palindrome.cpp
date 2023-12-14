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
 
struct Hash {
	static const i64 P;
	static i64 B;
	vector<i64> pw, h;
 
	i64 mul(i64 a, i64 b) {
		i128 c = (i128)a * b;
		c = (c & P) + (c >> 61);
		if(c >= P) c -= P;
		return c;
	}
 
	i64 sum(i64 a, i64 b) {
		a += b;
		if(a >= P) a -= P;
		return a;
	}
 
	Hash(string& s) {
		int n = s.size();
		pw.resize(n + 1);
		h.resize(n + 1);
		pw[0] = 1;
		h[0] = 0;
		for(int i = 1; i <= n; ++i) {
			pw[i] = mul(pw[i - 1], B);
			h[i] = sum(h[i - 1], mul(pw[i], s[i - 1]));
		}
	}
 
	i64 operator()(int l, int r) {
		int n = pw.size();
		return mul(pw[n-l-1], sum(h[r+1], P - h[l]));
	}
};
 
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
i64 uniform(i64 l, i64 r) {
	uniform_int_distribution<i64> uid(l, r);
	return uid(rng);
}
 
const i64 Hash :: P = (1ll << 61) - 1;
i64 Hash :: B = uniform(256, (1ll << 61) - 2);
 
void manacher(string& s, vector<int>& d1, vector<int>& d2) {
	int l = 0, r = -1, len = 0, n = s.size();
	d1.assign(n, 1);
	d2.assign(n, 0);
	for(int i = 0; i < n; ++i) {
		if(i <= r) {
			d1[i] = min(d1[l + r - i], r - i + 1);
			d2[i] = min(d2[l + r - i + 1], r - i + 1);
		}
		while(i + d1[i] < n && i - d1[i] >= 0 && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];
		while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];
		if(r < i + d2[i] - 1) l = i - d2[i], r = i + d2[i] - 1;
		if(r < i + d1[i] - 1) l = i - d1[i] + 1, r = i + d1[i] - 1;		
		if(r == n - 1) len = max(len, r - l + 1);
	}
}	
 
i64 f(string& s) {
	Hash hs(s);
	using T = pair<int, i64>;
	map<T, int, greater<T>> mp;
	map<i64, ii> interval;
	vector<int> d1, d2;
	int n = s.size();
	
	manacher(s, d1, d2);
 
	for(int i = 0; i < n; ++i) {
		i64 h = hs(i - d1[i] + 1, i + d1[i] - 1);
		++mp[{2 * d1[i] - 1, h}];
		interval[h] = {i - d1[i] + 1, i + d1[i] - 1};
		if(d2[i]) {
			h = hs(i - d2[i], i + d2[i] - 1);
			++mp[{2 * d2[i], h}];
			interval[h] = {i - d2[i], i + d2[i] - 1};
		}
	}
 
	i64 ans = 0;
 
	while(!mp.empty()) {
		auto [len, h] = mp.begin()->fi;
		int frq = mp.begin()->sc;
		ans = max(ans, (i64)len * frq);
		mp.erase(mp.begin());
		if(len <= 2) continue;
		auto [l, r] = interval[h];
		i64 nh = hs(l + 1, r - 1);
		mp[{len - 2, nh}] += frq;
		interval[nh] = {l + 1, r - 1};
	}
 
	return ans;
}
 
void solve() {
	string s;
	cin >> s;
	cout << f(s) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
