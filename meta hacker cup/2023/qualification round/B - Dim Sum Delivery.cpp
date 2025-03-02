#include "bits/stdc++.h"

using namespace std;

int kase = 1;

void solve() {
    int r, c, a, b;
    cin >> r >> c >> a >> b;
    cout << "Case #" << kase++ << ": ";
    if(r > c) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    while(t--) solve();

    return 0;
}

