#include "bits/stdc++.h"
 
using namespace std;
 
//#define INF   1000000000
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
 
const int N = 1e7 + 10, INF = 0x3f3f3f3f;
 
int steps[N], maxp[N], cur, pq[N];
 
void push(int a, int b) {
	pq[b] = max(pq[b], a);
}
 
int top(int r) {
	while(cur < N && pq[cur] <= r) ++cur;
	return cur < N ? cur : INF;
}
 
void solve() {
	int m, q;
	
	cin >> m >> q;
 
	memset(steps, 0x3f, sizeof steps);
	
	for(int i = 0; i < m; ++i) {
		int p;
		cin >> p;
		for(int j = 0; j < N; j += p) maxp[j] = p;
	}
 
	push(maxp[0], 1);
 
	for(int i = 1; i < N; ++i) {
		steps[i] = top(i);
		if(maxp[i] && steps[i] < INF) push(i + maxp[i], steps[i] + 1);	
	}
 
	while(q--) {
		int n;
		cin >> n;
		if(steps[n] == INF) {
			cout << "oo\n";
			continue;
		}
		cout << steps[n] << '\n';
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
