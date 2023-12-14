#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
 
const int N = 5e2 + 10, MOD = 1e9 + 7;
 
int c[N][N], fat[N], col[N];
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
 
    int n, r1A = 0, r1B = 0, r0 = 0, c0 = 0, fA = 0, fB = 0;
    i64 ans = 0;
    vector<int> fixedA, fixedB;
 
    cin >> n;
 
    c[0][0] = fat[0] = 1;
    for(int i = 1; i <= n; ++i) {
        c[i][0] = c[i][i] = 1;
        fat[i] = (i64)fat[i - 1] * i % MOD;
        for(int j = 1; j < i; ++j) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
    }
 
    for(int i = 0; i < n; ++i) {
        string s;
        int r_cnt = 0, v = -1;
        char ch = -1;
 
        cin >> s;
        
        for(int j = 0; j < n; ++j) {
            if(s[j] == '.') continue;
            if(s[j] == 'A') ++fA;
            else ++fB;
            ++col[j];
            ++r_cnt;
            v = j;
            ch = s[j];
        }
 
        if(r_cnt == 0) ++r0;
        else if(r_cnt == 1) {
            if(ch == 'A') fixedA.push_back(v);
            else fixedB.push_back(v);
        }
    }
 
    for(int i = 0; i < n; ++i) if(col[i] == 0) ++c0;
   
    for(int c : fixedA) if(col[c] == 1) ++r1B;
    for(int c : fixedB) if(col[c] == 1) ++r1A;
 
    for(int x = 0; x <= r0 && x <= c0; ++x) {
        for(int y = 0; y <= r1A; ++y) {
            for(int z = 0; z <= r1B; ++z) {
                i64 ways = (i64)c[r1A][y] * c[r1B][z] % MOD * c[r0][x] % MOD * c[c0][x] % MOD * fat[x] % MOD * fat[n - x - y - fA] % MOD * fat[n - x - z - fB];
                ans += (x + y + z) & 1 ? -ways : ways;
                ans %= MOD;
            }
        }
    }
    
    cout << (ans + MOD) % MOD << '\n';
 
    return 0;
}
