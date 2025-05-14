#include <bits/stdc++.h>
 
using namespace std;
 
const long long INF = 1e15L;
 
long long manhattan[4] = {-INF, -INF, -INF, -INF};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int t;
	long long ans {};
	
	cin >> t;
 
	while(t--) {
		int x, y;
		
 
		cin >> x >> y;
 
		for(int i = 0; i < 4; ++i) {
			long long dist = 0;
 
			if(i & 1) dist += x;
			else dist -= x;
 
			if(i & 2) dist += y;
			else dist -= y;
 
			manhattan[i] = max(manhattan[i], dist);
		}
 
		for(int i = 0; i < 4; ++i) {
			long long dist = 0;
 
			if(i & 1) dist += x;
			else dist -= x;
 
			if(i & 2) dist += y;
			else dist -= y;
 
			ans = max(ans, dist + manhattan[i ^ 3]);
		}
 
		cout << ans << '\n';
	}
 
	return 0;
}