#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e5 + 5;

bitset<N> coins;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, m;

    cin >> v >> m;

    coins[0] = 1;

    for(int i = 0; i < m; ++i) {
        int coin;

        cin >> coin;

        coins |= coins << coin;
    }

    if(coins[v])
        cout << "S\n";
    else
        cout << "N\n";

    return 0;
}