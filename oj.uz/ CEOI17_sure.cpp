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
	int n;
 
	cin >> n;
 
	vector<double> a(n), b(n);
 
	for(int i = 0; i < n; ++i) cin >> a[i] >> b[i];
		
	sort(a.rbegin(), a.rend());
	sort(b.rbegin(), b.rend());
 
	int i = 0, j = 0;
	double s[2] = {0}, ans = 0;
 
	while(i + j < n + n) {
		if(i < n && j < n) {
			if(s[0] < s[1]) s[0] += a[i++];
			else s[1] += b[j++];
		} else if(i < n) s[0] += a[i++];
		else s[1] += b[j++];
		ans = max(ans, min(s[0], s[1]) - i - j);
	}
 
	cout << fixed << setprecision(4) << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
