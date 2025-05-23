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

	vector<int> p(n);
	set<int> minQueue;

	for(int& v : p) cin >> v;

	for(int i = n - 1; i >= 0; --i) {
		int o = p[i];

		while(!minQueue.empty() && *minQueue.begin() < p[i]) {
			o = min(o, *minQueue.begin());
			minQueue.erase(minQueue.begin());
		}

		minQueue.insert(o);
	}

	cout << minQueue.size() << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 	cin >> t;
    while(t--) solve();
    return 0;
}

