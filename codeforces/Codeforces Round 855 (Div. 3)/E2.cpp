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
	int n, k;
	string s, t;
	cin >> n >> k >> s >> t;
	vector<bool> vis(n, false);
	for(int i = 0; i < n; ++i) {
		if(vis[i]) continue;
		string a, b;
		queue<int> q;
		vis[i] = true;
		q.push(i);
		while(!q.empty()) {
			int i = q.front(); q.pop();
			a += s[i], b += t[i];
			for(int p : {k, k + 1}) {
				for(int s : {-1, 1}) {
					int j = i + p * s;
					if(j >= 0 && j < n && !vis[j]) {
						vis[j] = true;
						q.push(j);
					}
				}
			}
		}
		sort(all(a)); sort(all(b));
		if(a != b) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	cin >> t;
	while(t--) solve();
	return 0;
}
