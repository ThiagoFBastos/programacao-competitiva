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
	int n;
	i64 sum = 0;
	cin >> n;
	priority_queue<int> pq;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		if(a) pq.push(a);
		else if(!pq.empty()) {
			sum += pq.top();
			pq.pop();
		}
	}
	cout << sum << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
