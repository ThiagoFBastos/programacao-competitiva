#include <bits/stdc++.h>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MOD = 131071;

    int mod = 0;

    for(string n; cin >> n; ) {
        for(char digit : n) {
            if(!isdigit(digit))
                continue;
            mod = (2 * mod + digit - '0') % MOD;
        }

        if(n.back() == '#') {
            cout << (mod ? "NO\n" : "YES\n");
            mod = 0;
        }
    }

    return 0;
}