#include "bits/stdc++.h"

using namespace std;

void solve(int test) {
    int n;

    cin >> n;

    vector<int> X(n);

    for(int& x : X) cin >> x;

    sort(X.begin(), X.end());

    cout << "Case #" << test << ": " << fixed << setprecision(9);

    if(n % 2 == 0 || n > 5) {
        double dist = (X.back() + X[n - 2] - X[0] - X[1]) / 2.0;
        cout << dist << '\n';
    } else {
        double dist = 0;
        for(int i = 1; i < n - 2; ++i) {
            double x = (X[n - 1] + X[i + 1] - X[i] - X[0]) / 2.0;
            dist = max(dist, x);
        }
        cout << dist << '\n';
    }
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

