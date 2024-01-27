#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
    int n;

    cin >> n;

    int64_t cnt {};
    int frq[2] = {0}, t = 0;

    while(n--) {
        int b;
        cin >> b;
        ++frq[t % 2];
        t += b;
        cnt += frq[(t & 1) ^ 1];
    }
    
    cout << cnt << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}

