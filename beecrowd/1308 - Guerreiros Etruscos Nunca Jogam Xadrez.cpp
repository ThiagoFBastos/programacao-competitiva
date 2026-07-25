#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

    size_t n;

    cin >> n;

    ranges::for_each(views::iota(size_t {}, n), [](auto) {
        long long n;

        cin >> n;
        
        auto k = static_cast<long long>(sqrt(2 * n + 0.0L));

        if(k * (k + 1) / 2 > n)
            --k;

        cout << k << '\n';
    });

	return 0;
}
 