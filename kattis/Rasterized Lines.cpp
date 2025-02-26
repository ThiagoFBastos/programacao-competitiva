#pragma GCC optimize("O3,unroll-loops")
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

const int N = 5e4 + 1;
bitset<N> isp;
vector<int> S;

i64 mod_sum(i64 x, i64 n) {
    return x >= n ? x - n : x;
}

i64 mulmod(i64 a, i64 b, i64 c) {
    return (__int128)a * b % c;
}

std::mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());

i64 exp(i64 a, i64 p, i64 n) {
    i64 ans = 1;
    for(; p > 0; p >>= 1) {
        if(p & 1) ans = (__int128)ans * a % n;
        a = (__int128)a * a % n;
    }
    return ans;
}

bool is_prime(i64 a, i64 d, int s, i64 n) {
    i64 x = exp(a, d, n);
    if(x == 1 || x == n - 1) return true;
    for(int k = 1; k < s; ++k) {
        x = (__int128)x * x % n;
        if(x == n - 1) return true;
    }
    return false;
}

bool is_prime(i64 p) {
    if(p < 4) return p == 2 || p == 3;
    int s = __builtin_ctzll(p - 1);
    i64 d = (p - 1) >> s;
    for(int i = 0; i < 5; ++i) if(!is_prime(rnd() % (p - 3) + 2, d, s, p)) return false;
    return true;
}

i64 pollard_rho(i64 n) {
    i64 x, y, c = rnd() % n, g = 1;
    x = y = rnd() % n;
    while(g == 1) {
        x = mod_sum(mulmod(x, x, n) + c, n);
        y = mod_sum(mulmod(y, y, n) + c, n);
        y = mod_sum(mulmod(y, y, n) + c, n);
        g = __gcd(abs(x - y), n);
        if(g == n) {
            g = 1;
            x = y = rnd() % n;
            c = rnd() % n;
        }
    }
    return g;
}

auto divisores(i64 N) {
    vector<i64> divisores {1};
    for(int k : S) {
        if((i64)k * k * k > N) break;
        else if(N % k) continue;
        int n = divisores.size();
        i64 p = 1;
        while(N % k == 0) {
            N /= k;
            p *= k;
            for(int j = 0; j < n; ++j) divisores.emplace_back(divisores[j] * p);
        }
    }
    if(N <= 1e9) {
        for(int k : S) {
            if((i64)k * k > N) break;
            else if(N % k) continue;
            int n = divisores.size();
            i64 p = 1;
            while(N % k == 0) {
                N /= k;
                p *= k;
                for(int j = 0; j < n; ++j) divisores.emplace_back(divisores[j] * p);
            }
        }
    }
    if(!is_prime(N) && N > 1) {
        i64 g = pollard_rho(N);
        int n = divisores.size();
        for(int i = 0; i < n; ++i) divisores.emplace_back(divisores[i] * g);
        N /= g;
        if(N == g) {
            for(int i = 0; i < n; ++i) divisores.emplace_back(divisores[i] * g * g);
            N /= g;
        }   
    }
    if(N > 1) {
        int n = divisores.size();
        for(int i = 0; i < n; ++i) divisores.emplace_back(divisores[i] * N);
    }
    return divisores;
}

void solve() {
    i64 N, cnt = 0;
    cin >> N;
    for(i64 x : divisores(N)) {
        i64 K = N + x;
        auto p = divisores(K);
        int n = size(p);
        sort(p.begin(), p.end());
        vector<i64> dp(n, 0);
        for(int i = n - 1; i >= 0; --i) {
            dp[i] += K / p[i] - 1;
            if(p[i] == x) {
                cnt += dp[i];
                break;
            }
            for(int j = i - 1; j >= 0; --j) {
                if(p[i] % p[j]) continue;
                dp[j] -= dp[i];
            }
        }
    }
    cout << cnt << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    isp.set();
    for(int k = 2; k * k < N; ++k) {
        if(!isp[k]) continue;
        for(int j = k * k; j < N; j += k) isp[j] = 0;
    }
    for(int k = 2; k < N; ++k) if(isp[k]) S.push_back(k);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}