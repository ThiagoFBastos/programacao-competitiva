#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

int gcd(int a, int b, i64& x, i64& y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	i64 _x, _y;
	int g = gcd(b, a % b, _x, _y);
	y = _x - (a / b) * _y;
	x = _y;	
	return g;
}

bool findSolution(int a, int b, int c, int& k) {
	int g = gcd(b, c);
	i64 x, y;

	if(a % g) return false;

	a /= g;
	b /= g;
	c /= g;
	
	gcd(b, c, x, y);
	
	k = (a * x % c + c) % c;

	return true;
}

void solve() {
	
	int n, s, k, x;

	cin >> n >> s >> k;

	s = (-s % n + n) % n;

	if(findSolution(s, k, n, x)) cout << x << '\n';
	else cout << "-1\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}

