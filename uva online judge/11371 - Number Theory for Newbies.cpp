#include <bits/stdc++.h>

using namespace std;

long long max_permutation_number(long long n) {
	int frq[10] = {0};
	long long result {};

	for(; n > 0; n /= 10)
		++frq[n % 10];

	for(int i = 9; i >= 0; --i)
		for(int j = 0; j < frq[i]; ++j)
			result = 10 * result + i;

	return result;
}

long long min_permutation_number(long long n) {
	int frq[10] = {0};
	long long result {};

	for(; n > 0; n /= 10)
		++frq[n % 10];

	auto it = find_if(frq + 1, frq + 10, [](int cnt) { return cnt != 0; });

	if(it != end(frq)) {
		int digit = it - frq;
		result = digit;
		--*it;
	}

	for(int i = 0; i < frq[0]; ++i)
		result = 10 * result;

	for(int i = 1; i <= 9; ++i)
		for(int j = 0; j < frq[i]; ++j)
			result = 10 * result + i;

	return result;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	long long n;

	while(cin >> n) {
		long long min_number = min_permutation_number(n);
		long long max_number = max_permutation_number(n);
		long long diff = max_number - min_number;

		cout << max_number << " - " << min_number << " = " << diff << " = 9 * " << diff / 9 << '\n';	
	}

	return 0;
}
 