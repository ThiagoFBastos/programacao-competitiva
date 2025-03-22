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

	int n, q;

	cin >> n >> q;

	vector<int> a(n + 1), lo(n + 1, 0), hi(n + 1, n + 1), pre(n + 1, 0), zeroes(n + 1, 0);
	map<int, int> last[2];
	
	for(int i = 1; i <= n; ++i) {
		cin >> a[i];
		zeroes[i] = (!a[i]) + zeroes[i - 1];
		pre[i] = a[i] ^ pre[i - 1];
		last[i % 2][pre[i - 1]] = i;
		if(last[i % 2].count(pre[i])) lo[i] = last[i % 2][pre[i]]; 
	}

	last[0].clear();
	last[1].clear();

	for(int i = n; i > 0; --i) {
		last[i % 2][pre[i]] = i;
		if(last[i % 2].count(pre[i - 1])) hi[i] = last[i % 2][pre[i - 1]];
	}

	while(q--) {
		int l, r;
		cin >> l >> r;
		if(pre[r] ^ pre[l - 1]) cout << "-1\n";
		else if(zeroes[r] - zeroes[l - 1] == r - l + 1) cout << "0\n";
		else if(r % 2 == l % 2) cout << "1\n";
		else {
			if(r - l + 1 == 2) cout << "-1\n";
			else if(!a[l] || !a[r]) cout << "1\n";
			else if(hi[l] <= r || lo[r] >= l) cout << "2\n";
			else cout << "-1\n";
		}
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 	//cin >> t;
	while(t--) solve();
	return 0;
}
