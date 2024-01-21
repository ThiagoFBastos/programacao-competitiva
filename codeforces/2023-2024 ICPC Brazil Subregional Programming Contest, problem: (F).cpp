#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
    int d, c, r;
    cin >> d >> c >> r;
    vector<int> C(c);
    for(int& v : C) cin >> v;
    for(int i = 0; i < r; ++i) {
        int v;
        cin >> v;
        d += v;
    }
    int ans = r;
    for(int v : C) {
        d -= v;
        if(d < 0) break;
        ++ans;
    }
    cout << ans << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}

