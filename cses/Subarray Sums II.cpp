#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n, t;
 
	scanf("%d%d", &n, &t);
 
	ll count = 0, S = 0;
	map<ll, int> pc;
 
	pc[0] = 1;
 
	for(int k = 0; k < n; ++k) {
 
		int x;
 
		scanf("%d", &x);
 
		S += x;
	
		if(pc.count(S - t))
			count += pc[S - t];
	
		++pc[S];
	}
 
	printf("%lld\n", count);
 
	return 0;
}
