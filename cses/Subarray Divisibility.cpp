#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n;
 
	scanf("%d", &n);
 
	ll S = 0, count = 0;
	vi mc(n, 0);
 
	mc[0] = 1;
 
	for(int k = 0; k < n; ++k) {
 
		int x, m;
 
		scanf("%d", &x);
 
		S += x;
		m = (S % n + n) % n;
 
		count += mc[m];
 
		++mc[m];
	}
 
	printf("%lld\n", count);
		
	return 0;
}
