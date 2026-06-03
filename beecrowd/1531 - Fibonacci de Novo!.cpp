#include <bits/stdc++.h>

using namespace std;

using matrix = array<array<long long, 2>, 2>;

matrix multiply(const matrix& a, const matrix& b, int m) {
    matrix c;
    
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            c[i][j] = 0;
            for(int k = 0; k < 2; ++k)
                c[i][j] += a[i][k] * b[k][j];
            c[i][j] %= m;
        }
    }

    return c;
}

matrix pow(matrix a, int p, int m) {
    matrix res {{{1, 0}, {0, 1}}};

    for(; p > 0; p >>= 1) {
        if(p & 1)
            res = multiply(res, a, m);

        a = multiply(a, a, m);
    }

    return res;
}

int fib(int n, int m) {
    if(n < 2)
        return n;

    matrix t = pow({{{0, 1}, {1, 1}}}, n - 2, m);

    return (t[1][0] + t[1][1]) % m;
}

vector<int> sieve(int n) {
    vector<int> f(n + 1, 0);

    for(int i = 2; i <= n; ++i) {
        if(f[i])
            continue;
        
        for(int j = i; j <= n; j += i)
            f[j] = i;
    }

    return f;
}

vector<pair<int, int>> factors(const vector<int>& max_factor, int n) {
    vector<pair<int, int>> factors;

    while(n > 1) {
        const int p = max_factor[n];

        int i = 0;

        do
        {
            ++i;
            n /= p;
        } while (n % p == 0);

        factors.emplace_back(p, i);
    }

    return factors;
}

vector<int> divisors(const vector<pair<int, int>>& fac) {
    vector<int> divs {1};

    for(auto [p, k] : fac) {
        const auto n = divs.size();
        long long power = 1;

        for(int i = 0; i < k; ++i) {
            power *= p;
            for(size_t j = 0; j < n; ++j)
                divs.push_back(divs[j] * power);
        }
    }

    return divs;
}

int phi(const vector<int>& max_factors, int p) {
    int n = p % 5 == 1 || p % 5 == 4 ? p - 1 : 2 * (p + 1);

    auto fac = factors(max_factors, n);

    auto divs = divisors(fac);

    sort(divs.begin(), divs.end());

    for(int d : divs) {
        if(fib(d, p) == 0 && fib(d + 1, p) == 1)
            return d;
    }

    throw exception();
}

int pisano(const vector<int>& max_factors, int m) {

    long long result = 1;

    auto facs = factors(max_factors, m);

    for(auto [p, k] : facs) {
        int period = 1;

        if(p == 2)
            period = 3;
        else if(p == 5)
            period = 20;
        else
            period = phi(max_factors, p);

        for(int i = 1; i < k; ++i)
            period *= p;

        result = lcm<long long>(result, period);
    }

    return static_cast<int>(result);
}

int fib_fib(const vector<int>& max_factors, int n, int m) {
    return fib(fib(n, pisano(max_factors, m)), m);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int N = 2e6 + 5;

    auto max_factors = sieve(N);

    int n, m;

    while(cin >> n >> m) {
        cout << fib_fib(max_factors, n, m) << '\n';
    }

    return 0;
}