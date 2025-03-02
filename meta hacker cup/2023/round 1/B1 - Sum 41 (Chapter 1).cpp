#include "bits/stdc++.h"

using namespace std;

void solve(int test) {
    int p;

    cin >> p;

    int sum = 0;
    vector<int> arr;

    for(int k = 2; k <= 41; ++k) {
        while(p % k == 0) {
            sum += k;
            p /= k;
            arr.push_back(k);
        }
    }
    cout << "Case #" << test << ": ";

    if(sum > 41 || p != 1) {
        cout << "-1\n";
        return;
    }

    while(sum < 41) {
        ++sum;
        arr.push_back(1);
    }

    cout << arr.size();

    for(int x : arr) cout << ' ' << x;
    cout << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

