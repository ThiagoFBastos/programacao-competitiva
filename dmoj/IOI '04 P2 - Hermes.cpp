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

const int N = 2002, inf = 1e9, skip = 1000;

int X[2][N], Y[2][N];

void solve() {

	int n;
	
	cin >> n;
	
	for(int i = 0; i < N; ++i) X[0][i] = Y[0][i] = inf;
	
	vector<ii> p(n + 1);
	
	p[0] = {skip, skip};
	X[0][skip] = 0;
	
	for(int i = 1; i <= n; ++i) {
		int x, y;
		
		cin >> x >> y;
		
		x += skip;
		y += skip;
		
		p[i] = {x, y};
		
		for(int i = 0; i < N; ++i) X[1][i] = Y[1][i] = inf;
		
		int preX = inf, preY = inf, c[4] = {inf, inf, inf, inf};
		
		auto [x0, y0] = p[i - 1];
		
		for(int i = 0; i < N; ++i) {
			preX = min(preX, abs(x - x0) - i + X[0][i]);
			preY = min(preY, abs(y - y0) - i + Y[0][i]);
			c[0] = min(c[0], abs(i - x) - y0 + Y[0][i]);
			c[1] = min(c[1], abs(i - y) - x0 + X[0][i]);
			c[2] = min(c[2], abs(i - x) + y0 + Y[0][i]);
			c[3] = min(c[3], abs(i - y) + x0 + X[0][i]);
			X[1][i] = min(X[1][i], preX + i);
			Y[1][i] = min(Y[1][i], preY + i);
		}
		
		preX = preY = inf;
		
		for(int i = N - 1; i >= 0; --i) {
			preX = min(preX, abs(x - x0) + i + X[0][i]);
			preY = min(preY, abs(y - y0) + i + Y[0][i]);
			X[1][i] = min(X[1][i], preX - i);
			Y[1][i] = min(Y[1][i], preY - i);
			if(i >= y0) X[1][i] = min(X[1][i], c[0] + i);
			if(i <= y0) X[1][i] = min(X[1][i], c[2] - i);
			if(i >= x0) Y[1][i] = min(Y[1][i], c[1] + i);
			if(i <= x0) Y[1][i] = min(Y[1][i], c[3] - i);
		}
		
		for(int i = 0; i < N; ++i) {
			X[0][i] = X[1][i];
			Y[0][i] = Y[1][i];
		}
	}
	
	cout << min(*min_element(X[0], X[0] + N), *min_element(Y[0], Y[0] + N)) << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
