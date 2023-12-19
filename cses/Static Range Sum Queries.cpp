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
 
	vll preffix(n + 1);
 
	for(int k = 0; k < n; ++k) {
 
		int x;
 
		cin >> x;
 
		preffix[k + 1] = x + preffix[k];
	}
 
	while(q--) {
 
		int l, r;
 
		cin >> l >> r;
 
		cout << preffix[r] - preffix[l - 1] << '\n';
	}
	
	return 0;
}
