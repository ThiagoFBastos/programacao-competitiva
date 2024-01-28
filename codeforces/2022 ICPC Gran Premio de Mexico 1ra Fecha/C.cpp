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

int n, q;
vector<int> a;

int bb(vector<tuple<int, int, int>>& b, i64 N) {
     int lo = 0, hi = n - 1;
       
     while(lo < hi) {
        int mid = (lo + hi) / 2;
        i64 cnt = 0;
            
        for(auto [l, r, x] : b)
            cnt += max(0ll, min(r, mid) - l + 1ll) * x;
        
        if(cnt >= N) hi = mid;
        else lo = mid + 1;
    }
    
    return hi;
    
}

void solve() {
  
    cin >> n >> q;
    
    a.resize(n);
    
    for(int& v : a) cin >> v;
    
    while(q--) {
        int m;
        
        cin >> m;
        
        vector<tuple<int, int, int>> b(m);
        i64 N = 0;
        
        for(int i = 0; i < m; ++i) {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            b[i] = {l, r, x};
            N += (r - l + 1ll) * x;
        }
    
        if(N & 1) cout << a[bb(b, (N + 1) / 2)] << '\n';
        else cout << fixed << setprecision(1) << (a[bb(b, N / 2)] + a[bb(b, N / 2 + 1)]) / 2.0 << '\n';
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


