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

int f(int x) {
	int s = 0;
	while(x > 0) {
		s += x % 10;
		x /= 10;
	}
	return s;
}

void solve() {
	int n;

	cin >> n;

	string s = to_string(n);
	int x = 0, y = 0, t = 0;

	for(char c : s) {
		int d = c - '0';
		x *= 10;
		y *= 10;
		if(d % 2 == 0) {
			x += d / 2;
			y += d / 2;
		} else {
			x += d / 2;
			y += d / 2;
			if(t == 0) ++x;
			else ++y;
			t ^= 1;
		}
	}

	cout << x << ' ' << y << '\n';
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
