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
using i128 = __int128;

i64 linearSum(int l, int r) {
    return (r - l + 1ll) * (r + l) / 2;
}

i64 f(int p, int n, int q) {
    p %= q;
    if(!n || !p) return 0;
    i64 sum = linearSum(0, q - 1) * (n / q);
    n %= q;
    int m = (i64)p * n / q;
    i64 mod = (i64)m * n - (q * linearSum(1, m) - f(q % p, m, p)) / p;
    sum += p * linearSum(1, n) - mod * q;
    return sum;
}

i64 g(int p, int n, int q) {
    int g = gcd(p, q);
    return f(p / g, n, q / g) * g;
}

void solve() {
    int p, q, n;
    cin >> p >> q >> n;
    cout << g(p, n, q) << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}