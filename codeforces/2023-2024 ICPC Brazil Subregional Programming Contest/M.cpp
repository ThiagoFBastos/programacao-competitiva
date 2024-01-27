#include <bits/stdc++.h>

using namespace std;

const int N = 100, INF = 1e9;

int d[N][N], dist[N][N];

void solve(int test) {
    int n;

    cin >> n;

    vector<tuple<int, int, int>> S;

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> d[i][j];
            dist[i][j] = INF;
            S.push_back({d[i][j], i, j});
        }
    }

    sort(S.begin(), S.end());
    
    int ans = 0;

    for(auto [w, i, j] : S) {
        if(dist[i][j] < w) {
            cout << "-1\n";
            return;
        } else if(dist[i][j] == w) ++ans;
        else {
            dist[i][j] = w;
            for(int a = 0; a < n; ++a)  
            for(int b = 0; b < n; ++b)
                dist[a][b] = min(dist[a][b], dist[a][i] + w + dist[j][b]);
        }
    }

    cout << ans / 2 << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}

