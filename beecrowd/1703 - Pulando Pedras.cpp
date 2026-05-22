#include <bits/stdc++.h>

using namespace std;

int count_divisors(int n, int m) {
    int cnt {};

    for(int i = 1; i * i <= n; ++i) {
        if(n % i == 0) {
            cnt += i <= m;

            if(i * i != n)
                cnt += n / i <= m;
        }
    }

    return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	size_t n;

    cin >> n;

    ranges::for_each(views::iota(size_t{}, n), [](auto) {
        int n, k;

        cin >> n >> k;

        cout.precision(12);
        cout.setf(ios_base::fixed);

        if(n == 1)
            cout << 1.0 << '\n';
        else
            cout << 1.0L * count_divisors(k, n) / n << '\n';
    });

	return 0;
}