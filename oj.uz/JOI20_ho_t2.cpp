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
 
const int inf = 1e9;
 
void solve() {	
	int n, k, ans = inf;
	string s;
 
	cin >> n >> k >> s;
 
	vector<int> p[3];
	
	for(int i = 0; i < n; ++i) {
		if(s[i] == 'J') p[0].push_back(i);
		else if(s[i] == 'O') p[1].push_back(i);
		else p[2].push_back(i);
	}
 
	for(int i = 0; i < n; ++i) {
		if(s[i] != 'J') continue;
		int last = i;
		bool ok = true;
		for(int j = 0; j < 3; ++j) {
			int l = lower_bound(p[j].begin(), p[j].end(), last) - p[j].begin();
			if(l + k > (int)p[j].size()) {
				ok = false;
				break;
			}
			last = p[j][l + k - 1];
		}
		if(!ok) continue;
		ans = min(ans, last - i + 1 - 3 * k);
	}
 
	if(ans == inf) cout << "-1\n";
	else cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
