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
	string s;
	i64 cnt = 0;

	cin >> n >> s;

	for(int i = 0; i < n; ++i) {
		int frq[10] = {0}, m = 0, maxf = 0;
		for(int j = 0; j + i < n && j < 100; ++j) {
			if(frq[s[i + j] - '0']++ == 0) ++m;
			maxf = max(maxf, frq[s[i + j] - '0']);
			cnt += maxf <= m;
		}
	}

	cout << cnt << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


