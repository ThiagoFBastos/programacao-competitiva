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

const int N = 9, M = 108;
int m[] = {4, 5, 7, 9, 11, 13, 17, 19, 23};
int r[N];

i64 euclides_ext(i64 a, i64 b, i64& x, i64& y) {
	if(!b) {
		x = 1;
		y = 0;
		return a;
	}
	i64 _x, _y;
	i64 g = euclides_ext(b, a % b, _x, _y);
	y = _x - (a / b) * _y;
	x = _y;	
	return g;
}

i64 inv(i64 a, i64 m) {
	i64 x, y;
	a %= m;
	euclides_ext(a, m, x, y);
	return (x % m + m) % m; 
}

i64 crt(int r[], int m[], int n) {
	i64 x = 0, y = 1;
	for(int i = 0; i < n; ++i) {
		i64 z = 1;
		y *= m[i];
		for(int j = 0; j < n; ++j) {
			if(i == j) continue;
			z *= m[j];
		}
		x += r[i] * inv(z, m[i]) % m[i] * z;
	}
	x %= y;
	return x;
}

void solve() {
	cout << M << '\n';
	cout.flush();

	vector<int> A, B(M);

	for(int i = 0, l = 1; i < N; ++i) {
		for(int j = 1; j < m[i]; ++j) A.pb(l + j);
		A.pb(l);
		l += m[i];
	}

	for(int x : A) cout << x << ' ';
	cout << '\n';

	cout.flush();

	for(int& v : B) cin >> v;

	for(int i = 0, l = 0; i < N; ++i) {
		r[i] = find(A.begin() + l, A.begin() + l + m[i], B[l]) - A.begin() - l+1;		
		l += m[i];
	}

	cout << crt(r, m, N) << '\n';
	cout.flush();
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
