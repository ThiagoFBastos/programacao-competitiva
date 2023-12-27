#include "bits/stdc++.h"

using namespace std;
 
#define INF   1000000000
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
using i128 = __int128;

void solve() {	
	int n, pairs = 0;
	cin >> n;
	multiset<int, greater<int>> S;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;	
		S.insert(a);
	}
	while(!S.empty()) {
		int a = *S.begin();
		S.erase(S.begin());
		int p = 1 << (31 - __builtin_clz(2 * a));
		auto it = S.find(p - a);
		if(it != S.end()) {
			++pairs;
			S.erase(it);
		}
	}
	cout << pairs << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
