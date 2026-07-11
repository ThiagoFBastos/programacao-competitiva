#include <bits/stdc++.h>

using namespace std;

constexpr unsigned MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    cin >> n;

    auto rng = views::iota(0, n) | views::transform([](auto) {
        unsigned long long value;
        cin >> value;
        return value;
    });

    vector<int> bits(64, 0);

    ranges::for_each(rng, [&bits](auto value) {
        while(value) {
            int bit = __builtin_ctzll(value);
            ++bits[bit];
            value ^= 1llu << bit;
        }
    });

    unsigned long long answer {};

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < 64; ++j) {
            if(bits[j] && (bits[j] & i) == i)
                answer += 1llu << j;
            answer %= MOD;
        }
    }

    cout << answer << '\n';

    return 0;
}