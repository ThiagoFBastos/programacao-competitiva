#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
	int64_t ans {};
 
	cin >> n;
	
	vector<int> a(n);
	map<int, int> frq;
	int lo = 0;
 
	for(int& v : a) cin >> v;
 
	for(int i = 0; i < n; ++i) {
		++frq[a[i]];
 
		while(frq[a[i]] > 1)
			--frq[a[lo++]];
		
		ans += i - lo + 1;
	}
 
	cout << ans << '\n';
 
	return 0;
}