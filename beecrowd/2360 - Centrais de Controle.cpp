#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e3 + 5, MOD = 1e9 + 7;

vector<int> adj[N];
long long dp[N][3], n;

void dfs(int u, optional<int> p) {
    int only_adjacency = 1;

    // 0 - sem central
    // 1 - com central
    // 2 - adjacente a uma central

    dp[u][0] = dp[u][1] = dp[u][2] = 1;

    for(int v : adj[u]) {
        if(p && *p == v)
            continue;

        dfs(v, u);

        dp[u][0] = dp[u][0] * dp[v][2] % MOD;
        dp[u][1] = dp[u][1] * (dp[v][0] + dp[v][1] + dp[v][2]) % MOD;
        dp[u][2] = dp[u][2] * (dp[v][1] + dp[v][2]) % MOD;
        only_adjacency = only_adjacency * dp[v][2] % MOD;
    }

    dp[u][2] = (dp[u][2] - only_adjacency + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin >> n) {

        for(int i = 0; i < n; ++i)
            adj[i].clear();

        for(int i = 1; i < n; ++i) {
            int a, b;

            cin >> a >> b;

            --a, --b;

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        if(n == 1) {
            cout << "1\n";
            continue;
        }

        dfs(0, nullopt);

        int answer = (dp[0][1] + dp[0][2]) % MOD;

        cout << answer << '\n';
    }

    return 0;
}