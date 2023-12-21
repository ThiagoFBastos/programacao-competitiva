#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
#define fi first
#define sc second
 
int main() {
 
	int n, x;
 
	scanf("%d%d", &n, &x);
 
	vii a(n);
 
	for(int k = 0; k < n; ++k) {
 
		scanf("%d", &a[k].fi);
		a[k].sc = k + 1;
	}
 
	sort(a.begin(), a.end(), [](ii a, ii b) {return a.fi < b.fi;});
 
	int lo = 0, hi = n - 1;
 
	while(lo < hi) {
 
		if(a[lo].fi + a[hi].fi >= x)
			--hi;
 
		else
			break;
	}
 
	for(int k = lo; k <= hi; ++k) {
 
		int L = lo, R = hi, X = x - a[k].fi;
	
		while(L < k && R > k) {
 
			int Y = a[L].fi + a[R].fi;
 
			if(Y > X)
				--R;
 
			else if(Y < X)
				++L;
 
			else
				break;
		}
 
		if(L < k && R > k) {
 
			printf("%d %d %d\n", a[k].sc, a[L].sc, a[R].sc);
			return 0;
		}
	}
 
	puts("IMPOSSIBLE");
	
	return 0;
}
