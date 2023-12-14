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
 
void solve() {
 
	int n, k;
	i64 ans = 0;
		
	cin >> n >> k;
	
	vector<int> a(n);
	priority_queue<int> pq;
	
	for(int& v : a) cin >> v;
	
	for(int i = 1; i < n; ++i) pq.push(-a[i] + a[i - 1]);
	
	while(n > k) {
		int t = -pq.top();
		pq.pop();
		ans += t;
		--n;
	}
	
	cout << ans + k << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}
