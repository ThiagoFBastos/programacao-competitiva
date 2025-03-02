#include "bits/stdc++.h"

using namespace std;

int kase = 1;

void solve() {
    int s, d, k;

    cin >> s >> d >> k;

    cout << "Case #" << kase++ << ": ";

    if(s + 2 * d >= k && 2 * (s + d) >= k + 1)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    while(t--) solve();

    return 0;
}

