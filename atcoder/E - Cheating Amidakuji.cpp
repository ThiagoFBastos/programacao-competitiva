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

const int N = 2e5 + 100;

set<int> pos[N];

void operate(int a, int b, int card) {
	if(a == b) return;

	bool onA = pos[a].count(card);
	bool onB = pos[b].count(card);

	swap(pos[a], pos[b]);

	pos[a].erase(card);
	pos[b].erase(card);

	if(onA) pos[a].insert(card);
	if(onB) pos[b].insert(card);
}

void solve() {
	int n, m;

	cin >> n >> m;

	vector<int> a(m + 1);

	for(int i = 1; i <= m; ++i) cin >> a[i];

	for(int i = 1; i <= m; ++i)	pos[1].insert(i);

	for(int i = 1; i <= m; ++i) operate(a[i], a[i] + 1, i);
	
	vector<int> ans(m + 1);

	for(int i = 1; i <= n; ++i)
		for(int j : pos[i])
			ans[j] = i;

	for(int i = 1; i <= m; ++i) cout << ans[i] << '\n';
}	
 
int main() {
    ios_base :: sync_with_stdio(false);
   	cin.tie(0);
    int t = 1;
 	//cin >> t;
    while(t--) solve();
    return 0;
}
