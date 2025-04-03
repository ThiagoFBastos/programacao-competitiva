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

std::mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());


void solve() {

	int t1, t2, N;
	
	cin >> t1 >> t2 >> N;

	t1 = t2 = (t2 - t1) * 60;
	
	i64 A1, A2;
	
	A1 = A2 = 0;
	
	if(N <= t2) {
		int base = t2 - N;
		if(N + t1 > t2) A1 = 1ll * base * (t2 - N);
		else A1 = t1 * (base + t2 - t1 - N + 0ll);
	}
	
	if(N <= t1) {
		int base = t1 - N;
		if(N + t2 > t1) A2 = 1ll * base * (t1 - N);
		else A2 = t2 * (base + t1 - t2 - N + 0ll);
	}
	
	i64 P = 2ll * t1 * t2 - A1 - A2, Q = 2ll * (i64)t1 * t2;
	i64 g = gcd(P, Q);
	
	P /= g, Q /= g;
	cout << P << '/' << Q << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}