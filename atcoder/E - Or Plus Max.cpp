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

const int N = 1 << 18;

ii max1A[N], max2A[N];
int best[N];

void solve() {
	int n;

	cin >> n;

	for(int i = 0; i < (1 << n); ++i) {
		int a;

		cin >> a;

		max1A[i] = {a, i};
		max2A[i] = {-INF, -1};
		best[i] = -INF;
		
		for(int j = 0; j < n; ++j) {
			if(~i & (1 << j)) continue;

			int k = i ^ (1 << j);

			best[i] = max(best[i], best[k]);

			if(max1A[i] < max1A[k]) {
				max2A[i] = max(max1A[i], max2A[k]);
				max1A[i] = max1A[k];
			} else if(max1A[i] != max1A[k]) max2A[i] = max(max2A[i], max1A[k]);
			else max2A[i] = max(max2A[i], max2A[k]);
		}

		best[i] = max(best[i], max1A[i].fi + max2A[i].fi);
	}

	for(int i = 1; i < (1 << n); ++i) {
		best[i] = max(best[i], best[i - 1]);
		cout << best[i] << '\n'; 	
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
