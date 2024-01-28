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

const int N = 1e2 + 1, MOD = 1e9 + 7;

using matrix = array<array<int, N>, N>;

matrix mul(matrix& a, matrix& b, int n) {
    matrix c;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            c[i][j] = 0;
            for(int k = 0; k < n; ++k)
                c[i][j] = (1ll * a[i][k] * b[k][j] + c[i][j]) % MOD;
        }
    }
    return c;
}

matrix matrix_exp(matrix& a, int n, int p) {
    matrix ans;
    
    for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
        ans[i][j] = i == j;
    
    for(; p > 0; p >>= 1) {
        if(p & 1) ans = mul(ans, a, n);
        a = mul(a, a, n);
    }
    
    return ans;
}

void solve() {
    int n, m, k;
    
    cin >> n >> m >> k;
    
    matrix A;
    
    for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
        A[i][j] = 0;
        
    while(m--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        A[a][b] = A[b][a] = 1;
    }
    
    auto B = matrix_exp(A, n, k);
    
    int ans = 0;
    
    for(int i = 0; i < n; ++i) ans = (ans + B[0][i]) % MOD;
        
    cout << ans << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}


