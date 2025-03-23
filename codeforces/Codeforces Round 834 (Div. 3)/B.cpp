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
	int n, s;

	cin >> n >> s;

	set<int> S;

	for(int i = 0; i < n; ++i) {
		int v;
		cin >> v;
		S.insert(v);
	}

	for(int i = 1; i < *S.rbegin(); ++i) {
		if(S.count(i)) continue;
		s -= i;
	}

	for(int i = *S.rbegin() + 1; i <= 1000 && s > 0; ++i) s -= i;

	cout << (s == 0 ? "YES\n" : "NO\n");
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}


