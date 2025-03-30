#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base :: sync_with_stdio(false); 
    cin.tie(0);
    cout.tie(0);
    const int mod = 1e9 + 7;
    string s;
    int res = 0, q = 0, qf = 0, o = 0, n;
    cin >> s;
    n = s.size();
    vector<int> p(n + 1);
    p[0] = 1;
    for(int k = 1; k <= n; ++k) {
        if(s[k - 1] == '?') ++qf;
        p[k] = p[k - 1] << 1;
        if(p[k] >= mod) 
            p[k] -= mod;
    }
    for(int k = n - 1; k >= 0; --k) {
        if(s[k] == '?') --qf;
        if(s[k] != '0') {
            long long C = (p[q] * (n - 1LL - o - k) - (q ? 1LL * q * p[q - 1] : 0)) % mod;
            res = (res + C * p[qf]) % mod;
            if(res < 0) res += mod;
        }
        if(s[k] == '?') ++q;
        else if(s[k] == '1') ++o;
    }
    cout << res << '\n';
    return 0;
}