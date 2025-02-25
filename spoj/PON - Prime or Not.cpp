#pragma GCC optimize("O3", "unroll-loops")

#include "bits/stdc++.h"

using namespace std;

using ll = long long;

std::mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

ll exp(ll a, ll p, ll n) {
	ll ans = 1;
	for(; p > 0; p >>= 1) {
		if(p & 1) ans = (__int128)ans * a % n;
		a = (__int128)a * a % n;
	}
	return ans;
}

bool is_prime(ll a, ll d, int s, ll n) {
	ll x = exp(a, d, n);
	if(x == 1 || x == n - 1) return true;
	for(int k = 1; k < s; ++k) {
		x = (__int128)x * x % n;
		if(x == n - 1) return true;
	}
	return false;
}

bool is_prime(ll p) {
	if(p < 4) return p != 1;
	int s = __builtin_ctzll(p - 1);
	ll d = (p - 1) >> s;
	for(int i = 0; i < 5; ++i) if(!is_prime(rnd() % (p - 3) + 2, d, s, p)) return false;
	return true;
}

void solve() {
	ll n;
	cin >> n;
	cout << (is_prime(n) ? "YES\n" : "NO\n");	
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}