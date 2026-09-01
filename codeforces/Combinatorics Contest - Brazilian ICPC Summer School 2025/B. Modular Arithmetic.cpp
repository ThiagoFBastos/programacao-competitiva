#include <iostream>
#include <string>

constexpr int MOD = 1e9 + 7;

int operator%(std::string n, int mod) {
    int ans {};

    for(char digit : n)
        ans = (10LL * ans + digit - '0') % mod;

    return ans;
}

int64_t bin_exp(int64_t n, int p) {
    int64_t ans = 1;
    for(; p; p >>= 1) {
        if(p & 1)
            ans = ans * n % MOD;
        n = n * n % MOD;
    }
    return ans;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::string x, y;
    char op;

    std::cin >> x >> op >> y;

    switch(op) {
        case '+':
            std::cout<<(x%MOD+y%MOD)%MOD<<'\n';
            break;
        case '-':
            std::cout<<((x%MOD-y%MOD)%MOD+MOD)%MOD << '\n';
            break;
        case '*':
            std::cout<<1LL*(x%MOD)*(y%MOD)%MOD <<'\n';
            break;
        case '^':
            std::cout<<bin_exp(x%MOD, y%(MOD-1)) << '\n';
            break;
    }

    return 0;
}