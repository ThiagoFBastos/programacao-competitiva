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

i64 exp(i64 n, i64 p, i64 mod) {
    i64 ans = 1;
    for(; p > 0; p >>= 1) {
        if(p & 1) ans = ans * n % mod;
        n = n * n % mod;
    }
    return ans;
}

const int mod[] = {1004535809, 1092616193, 998244353};
const int root[] = {12289, 23747, 15311432};
const int root_1[] = {313564925, 642907570, 469870224};
const int root_pw[] = {1 << 21, 1 << 21, 1 << 23};

void ntt(vector<int>& a, bool invert, int m) {
    int n = a.size();

    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for(; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }

    for(int len = 2, wlen; len <= n; len <<= 1) {
        wlen = invert ? root_1[m] : root[m];

        for(int i = len; i < root_pw[m]; i <<= 1)
            wlen = (i64)wlen * wlen % mod[m];

        for(int i = 0; i < n; i += len) {
            for(int j = 0, w = 1; j < len / 2; ++j) {
                i64 u = a[i + j], v = (i64)a[i + j + len / 2] * w % mod[m];
                a[i + j] = u + v < mod[m] ? u + v : u + v - mod[m];
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod[m];
                w = (i64)w * wlen % mod[m];
            }
        }           
    }

    if(invert) {
        i64 x = exp(n, mod[m] - 2, mod[m]);
        for(int& y : a) y = (i64)y * x % mod[m];        
    }
}

vector<int> convolution(vector<int>& a, vector<int>& b, int m) {
    int n = 1;
    while(n < (int)max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false, m);
    ntt(b, false, m);
    vector<int> res(n);
    for(int i = 0; i < n; ++i) res[i] = (i64)a[i] * b[i] % mod[m];  
    ntt(res, true, m);
    return res;
}

const int N = 1e3 + 5;

int c[N][N];

void solve() {

    int H, W;
    int h, w;

    vector<tuple<int, int, int>> best;

    cin >> w >> h;

    for(int i = 0; i < h; ++i)
        for(int j = 0; j < w; ++j)
            cin >> c[i][j];

    cin >> W >> H;

    vector<int> P1(H * W), Q1(H * W);
    vector<int> P2(H * W), Q2(H * W);

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            Q1[i * W + j] = c[h - i - 1][w - j - 1];
            Q2[i * W + j] = 1 - c[h - i - 1][w - j - 1];
        }
    }

    for(int i = 0; i < H; ++i) {
        for(int j = 0; j < W; ++j) {
            int c;
            cin >> c;
            P1[i * W + j] = c;
            P2[i * W + j] = 1 - c;
        }
    }
    
    auto R1 = convolution(P1, Q1, 2);
    auto R2 = convolution(P2, Q2, 2);

    for(int i = 0; i <= H - h; ++i) {
        for(int j = 0; j <= W - w; ++j) {
            int dot = R1[(i + h - 1) * W + (w - 1 + j)];
            dot += R2[(i + h - 1) * W + (w - 1 + j)];
            best.pb({dot, -j, -i});
        }
    }

    sort(rall(best));

    for(auto [dot, x, y] : best) if(dot == get<0>(best[0])) cout << -x << ' ' << -y << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
 // cin >> t;
    while(t--) solve();
    return 0;
}