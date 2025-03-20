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
	string s[2];
	bool flag = true;
	int m;

	cin >> m;

	cin >> s[0] >> s[1];


	int r = -1, c = -1;

	for(int j = 0; j <= m; ++j) {
		if(s[0][j] == 'W') {
			if(c != -1) {
				if((j - c) % 2 && r != 0) flag = false;
				if((j - c) % 2 == 0 && r == 0) flag = false;
			}
			r = 0, c = j;
		} else if(s[1][j] == 'W') {
			if(c != -1) {
				if((j - c) % 2 && r != 1) flag = false;
				if((j - c) % 2 == 0 && r == 1) flag = false;
			}
			r = 1, c = j;
		}
	}

	cout << (flag ? "YES\n" : "NO\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}
