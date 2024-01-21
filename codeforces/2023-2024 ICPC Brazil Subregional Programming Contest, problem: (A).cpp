#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
    int n, H;
    cin >> n >> H;
    int ans {};
    while(n--) {
        int h;
        cin >> h;
        ans += h <= H;
    }
    cout << ans << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}

