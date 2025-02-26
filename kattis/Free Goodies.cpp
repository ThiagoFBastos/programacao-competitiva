#include "bits/stdc++.h"
using namespace std;
using tt = tuple<int, int, int>;
signed main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<tt> a(n), b(n);
        vector<int> pb(n), p(n, 1);
        int X = 0, Y = 0;
        for(int i = 0; i < n; ++i) {
            int x, y;
            cin >> y >> x;
            a[i] = {x, -y, i};
            b[i] = {y, -x, i};
            Y += y;
        }
        sort(a.rbegin(), a.rend());
        sort(b.rbegin(), b.rend());
        for(int i = 0; i < n; ++i) pb[get<2>(b[i])] = i;
        if(s == "Jan") {
            for(int i = 0, j = 1; j <= (1 + n) / 2; ++i) {
                bool ok = true;
                int cnt = 0;
                p[pb[get<2>(a[i])]] = 0;
                for(int k = 1; k <= n; ++k) {
                    cnt += p[k - 1];
                    ok = ok && cnt >= k / 2;
                }
                if(ok) {
                    X += get<0>(a[i]);
                    Y += get<1>(a[i]);
                    ++j;
                }
                else p[pb[get<2>(a[i])]] = 1;
            }
        } else {
            for(int i = 0, j = 1; j <= n / 2; ++i) {
                bool ok = true;
                int cnt = 0;
                p[pb[get<2>(a[i])]] = 0;
                for(int k = 1; k <= n; ++k) {
                    cnt += p[k - 1];
                    ok = ok && cnt >= (1 + k) / 2;
                }
                if(ok) {
                    X += get<0>(a[i]);
                    Y += get<1>(a[i]);
                    ++j;
                }
                else p[pb[get<2>(a[i])]] = 1;
            }
        }
        cout << Y << ' ' << X << '\n';
    }
    return 0;
}
