#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	
	int n;
	char c;
	string s;
	
	cin >> n >> c >> s;

	s += s;

	int ans = 0;

	vector<int> last(26, -1);

	for(int i = 2 * n - 1; i >= 0; --i) {
		last[s[i] - 'a'] = i;
		if(s[i] == c && last['g' - 'a'] != -1)
			ans = max(ans, last['g' - 'a'] - i);
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	cin >> t;
	while(t--) solve();
	return 0;
}
