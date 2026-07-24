#include "bits/stdc++.h"

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	size_t t;

    cin >> t;

    ranges::for_each(views::iota(size_t {}, t), [](auto) {
        unsigned d;
        unsigned long long n;

        cin >> d;

        vector<int> digits(d);

        for(auto& value : digits)
            cin >> value;

        cin >> n;

        sort(digits.begin(), digits.end());
        
        auto it = unique(digits.begin(), digits.end());

        digits.erase(it, digits.end());

        string kth;

        while(n > 0) {
            int digit = (n - 1) % d;
            kth += digits[digit] + '0';
            n = (n - digit) / d;
        }

        reverse(kth.begin(), kth.end());

        cout << kth << '\n';
    });

	return 0;
}
 