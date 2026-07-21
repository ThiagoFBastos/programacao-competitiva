#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1'000'000 + 5;

long long fat_mod[N], n2[N], n5[N];

int binExp(long long n, long long p, int mod) {
    long long ans {1};

    for(; p; p >>= 1) {
        if(p & 1)
            ans = ans * n % mod;
        n = n * n % mod;
    }

    return ans;
}

auto decomp(int n) {
    int cnt_2 {0}, cnt_5 {0};

    for(; n % 2 == 0; n /= 2) ++cnt_2;
    for(; n % 5 == 0; n /= 5) ++cnt_5;

    return make_tuple(n, cnt_2, cnt_5);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fat_mod[1] = 1;   

    for(int i = 2; i < N; ++i) {
        auto [n, cnt_2, cnt_5] = decomp(i);
        fat_mod[i] = fat_mod[i - 1] * n % 10;
        n2[i] = n2[i - 1] + cnt_2;
        n5[i] = n5[i - 1] + cnt_5;
    }

    int n;

    for(int i = 1; cin >> n; ++i) {

        int last_non_zero_digit = fat_mod[n] * binExp(2, n2[n] - n5[n], 10) % 10;

        cout << "Instancia " << i << '\n';
        cout << last_non_zero_digit << '\n';
        cout << '\n';
    }

    return 0;
}