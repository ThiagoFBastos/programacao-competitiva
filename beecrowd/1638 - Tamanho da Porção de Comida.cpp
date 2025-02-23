#include "bits/stdc++.h"

using namespace std;

const int inf = 1e6;

void solve() {
	
	int n, a, b;
	
	cin >> n >> a >> b;
	
	if(!n) exit(0);
	
	vector<int> c(n);
	int soma = 0;
	
	for(int i = 0; i < n; ++i) {
		cin >> c[i];
		soma += c[i];
	}
	
	sort(c.begin(), c.end());
	
	auto ans = make_pair(inf, 0);
	
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j <= n; ++j) {
			int L = 6 * c[i], R = inf;
			
			if(i + 1 < j) {
				L = max(L, 3 * c[j - 1]);
				R = min(R, 6 * c[i + 1]);
			}
			
			if(j < n) {
				L = max(L, 2 * c[n - 1]);
				R = min(R, 3 * c[j]);
			}
			
			if(L >= R) continue;
			
			int Y = (i + 1) + 2 * (j - i - 1) + 3 * (n - j);
			int X = L * Y - 6 * soma;
			
			ans = min(ans, make_pair(a * X + 6 * b * Y, L));
		}
		
		int L = 3 * c[i], R = 6 * c[0];
		
		if(i < n - 1) {
			L = max(L, 2 * c[n - 1]);
			R = min(R, 3 * c[i + 1]);
		}
		
		if(L >= R) continue;
		
		int Y = 2 * (i + 1) + 3 * (n - i - 1);
		int X = L * Y - 6 * soma;
		ans = min(ans, make_pair(a * X + 6 * b * Y, L));
	}
	
	{
		int L = 2 * c[n - 1], R = 3 * c[0];
		
		if(L < R) {
			int Y = 3 * n;
			int X = L * Y - 6 * soma;
			ans = min(ans, make_pair(a * X + 6 * b * Y, L));	
		}
	}
	
	int x, y = 0, z, L = ans.second, g;
	
	for(int i = 0; i < n; ++i) y += (int)ceil(6.0 * c[i] / L);
	
	x = L * y - 6 * soma;
	z = a * x + 6 * b * y;
	g = gcd(z, 6);
	z /= g;
	
	if(g == 6) cout << z << '\n';
	else cout << z << " / " << 6 / g << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	for(;;) solve();
	return 0;
}