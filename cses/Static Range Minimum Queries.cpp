#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using vi = vector<int>;
using vll = vector<ll>;
 
int main() {
 
	int n, q;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	cin >> n >> q;
 
	int **st = new int*[n];
	vi x(n), LOG(n + 1);
 
	LOG[1] = 0;
 
	for(int k = 2; k <= n; ++k)
		LOG[k] = 1 + LOG[k >> 1];
 
	int c = LOG[n];
 
	for(int k = 0; k < n; ++k) {
 
		st[k] = new int[c + 1];
		cin >> x[k];
 
		st[k][0] = x[k];
	}	
	
	for(int k = 1; k <= c; ++k)
		for(int i = 0; i + (1 << k) - 1 < n; ++i)
			st[i][k] = min(st[i][k - 1], st[i + (1 << k - 1)][k - 1]);
 
	while(q--) {
 
		int l, r;
 
		cin >> l >> r;
 
		--l, --r;
 
		int i = LOG[r - l + 1];
	
		cout << min(st[l][i], st[r - (1 << i) + 1][i]) << '\n';		
	}
 
	return 0;
}
