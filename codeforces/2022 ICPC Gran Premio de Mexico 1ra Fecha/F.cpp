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

const int N = 2, MOD = 1e9 + 7;

using matrix = array<array<int, N>, N>;

matrix mul(matrix& a, matrix& b) {
    matrix c;
            
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            c[i][j] = 0;
            for(int k = 0; k < 2; ++k)
                c[i][j] = (c[i][j] + 1ll * a[i][k] * b[k][j]) % MOD;
        }
    }
    
    return c;
}

matrix matrix_exp(matrix a, int p) {
    matrix b;
    
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < 2; ++j)    
            b[i][j] = i == j; 
            
    for(; p > 0; p >>= 1) {
        if(p & 1) b = mul(b, a);
        a = mul(a, a);   
    }
    
    return b;
}

int fib(int n) {
    if(n <= 2) return 1;
    
    matrix T;
    
    T[0][0] = 1;
    T[0][1] = 1;
    T[1][0] = 1;
    T[1][1] = 0; 
    
    auto A = matrix_exp(T, n - 2);
    
    return (A[0][0] + A[0][1]) % MOD;
}

void solve() {

    int n, m, last = -1;
    
    cin >> n >> m;
    
    vector<int> a, x(m);
    
    for(int& v : x) cin >> v;
    
    sort(all(x));
    
    for(int v : x) {
        a.pb(v - last - 1);
        last = v;
    }
    
    a.pb(n - last);
    
    i64 ans = 1;
    
    for(int v : a) {
        if(!v) ans = 0;
        ans = ans * fib(v) % MOD;
    }
    
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


