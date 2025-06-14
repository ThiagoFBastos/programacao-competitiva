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

const int inf = 1e9;

void solve() {
     
     int s, n, minpos = inf, ans = 0;
     
     cin >> s >> n;
     
     vector<int> a(n), rep(n), last(s + 1, inf), cnt(s + 1, 0);
     
     for(int& v : a) cin >> v;
     
     for(int i = n - 1; i >= 0; --i) {
        if(cnt[a[i]]++) minpos = min(minpos, last[a[i]]);
        rep[i] = minpos;
        last[a[i]] = i;
     }
     
     fill(cnt.begin(), cnt.end(), 0);
     
     for(int i = 0; i < s; ++i) {
        int flag = 1;
        if(n - i < s) break;
        for(int j = i; j < n; j += s) {
            if(rep[j] < j + s) {
                flag = 0;
                break;
            }
        }
        ans += flag;
        if(cnt[a[i]]++) break;
     }
     
     fill(cnt.begin(), cnt.end(), 0);
      
     for(int i = 1; i < n; ++i) {
        if(cnt[a[i - 1]]++) break;
        if(i < s && n - i < s && rep[i] > n) ++ans;
     }
     
    if(rep[0] > n) ans += s - n + (n != s);
     
     cout << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
    return 0;
}
