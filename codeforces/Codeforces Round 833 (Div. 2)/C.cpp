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

	cin >> n;

	vector<int> a(n);
	vector<i64> pre(n + 1, 0);
	map<i64, int> frq;
	int ans = 0;
	
	for(int& v : a) cin >> v;

	for(int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i - 1];

	for(int i = n - 1; i >= 0; --i) {
		++frq[pre[i + 1]];
		if(a[i] == 0) {
			int max_frq = 0;
			for(auto [_, v] : frq) max_frq = max(max_frq, v);
			ans += max_frq;		
			frq.clear();
		}
	}

	for(int i = 1; i <= n && a[i - 1]; ++i) ans += pre[i] == 0;

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


