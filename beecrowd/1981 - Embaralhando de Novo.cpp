#include <bits/stdc++.h>

using namespace std;

constexpr int N = 10000 + 5;
constexpr int MOD = 100000007;

long long fat[N], inv[N], inv_fat[N];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    for(int i = 0; i < 2; ++i)
        fat[i] = inv[i] = inv_fat[i] = 1;

    for(int i = 2; i < N; ++i) {
        fat[i] = i * fat[i - 1] % MOD;
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        inv_fat[i] = inv_fat[i - 1] * inv[i] % MOD;
    }

    for(string str; cin >> str; ) {
        if(str == "0")
            break;

        int frq[26] = {0};

        for(char c : str)
            ++frq[c - 'a'];

        auto n = str.size();

        auto answer = fat[n];

        for(int i = 0; i < 26; ++i)
            answer = answer * inv_fat[frq[i]] % MOD;

        cout << answer << '\n';
    }

	return 0;
}
 