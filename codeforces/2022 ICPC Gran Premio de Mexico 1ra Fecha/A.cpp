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

int n;
vector<i64> base, msb[64];
i64 xor_all = 0;

int lg(i64 x) {
    return 63 - __builtin_clzll(x);    
}

bool can(i64 X, i64 mask) {
    for(i64 x : base) {
        x &= mask;
        X = min(X, X ^ x);
    }
    return X == 0;
}

i64 max_xor_sum(int k, i64 X, bool gift) {
    if(k < 0) return X || gift || (int)base.size() != n ? 2 * X : -1;
    
    i64 mask = (1ll << k) - 1;
    
    if(can(X | (1ll << k), ~mask)) {
        i64 ans = max_xor_sum(k - 1, X | (1ll << k), true);
        if(ans != -1) return ans;
    }
    
    return max_xor_sum(k - 1, X, gift);
}

void solve() {

    cin >> n;
    
    vector<i64> a(n);
    
    for(i64& v : a) {
        cin >> v;
        xor_all ^= v;
    }
    
    for(i64& v : a) {
        v = v & ~xor_all;
        if(!v) continue;
        msb[lg(v)].pb(v);
    }
    
    for(int i = 49; i >= 0; --i) {
        auto& X = msb[i];
        if(X.empty()) continue;
        base.pb(X[0]);
        for(i64 y : X) {
            y ^= X[0];
            if(!y) continue;
            msb[lg(y)].pb(y);
        }
    }
    
    cout << xor_all + max_xor_sum(49, 0, false) << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}


