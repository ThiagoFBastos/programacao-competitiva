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

const int N = 1e5 + 100;

bool dp[N];

void solve() {
    int k, p;
    
    cin >> k >> p;
    
    dp[0] = 1;
    
    while(p--) {
        int r;
        cin >> r;
        for(int i = 0; i + r < N; ++i)
            dp[i + r] = dp[i + r] || dp[i];
    }
    
    vector<int> buy;
    
    for(int i = 1; i < N; ++i) if(dp[i]) buy.pb(i);
    
    while(k--) {
        int n;
        cin >> n;
        auto it = lower_bound(all(buy), n);
        cout << *it - n << '\n';
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


