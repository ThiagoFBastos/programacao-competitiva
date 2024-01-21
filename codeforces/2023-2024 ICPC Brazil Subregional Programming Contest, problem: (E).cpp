#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

int frq[N+10], S[N+10], F[N+10];

void solve(int test) {
    int n, k;

    cin >> n >> k;
    
    for(int i = 1; i <= N; ++i) {
        S[i] = S[i / 10] + i % 10;
        F[i] = i - S[i];
    }

    for(int i = 0; i < n; ++i) {
        int f;
        cin >> f;
        ++frq[f];
    }

    int i;

    for(i = N; i && k > 1; ) {
        if(frq[i] == 1) {
            --frq[i], ++frq[F[i]];
            --i;
            --k;
        } else if(frq[i] > 1) {
            int to = F[i];
            if(k - 1 >= frq[i]) {
                k -= frq[i];
                frq[to] += frq[i];
                frq[i] = 0;
                --i;
            } else 
                break;
        } else
            --i;
    }

    while(frq[i] == 0 && i >= 0) --i;

    cout << S[i] << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}



