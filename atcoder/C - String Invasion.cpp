#include "bits/stdc++.h"

using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

void solve() {
	string s;

	cin >> s;

	int n = s.size();
  	i64 ans = 0;
	
	deque<pair<int, char>> b;

	for(int i = n - 1; i >= 0; --i) {
		b.emplace_front(1, s[i]);
		while((int)b.size() > 1) {
			if(b[0].second != b[1].second) {	
				if(b[0].first == 1) break;
				ans += b[1].first;
				b[1].second = b[0].second;
			}
			b[1].first += b[0].first;
			b.pop_front();
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
 s
