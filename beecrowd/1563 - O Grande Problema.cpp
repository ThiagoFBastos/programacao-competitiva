#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#define soma(l, r) ((r - l + 1LL) * (r + l) >> 1)
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin >> n) {
		int K = sqrt(n);
		vector<int> r(K + 1);
		long long pairs = 0, m = 1LL * n * n;
		r[0] = n + 1;
		for(int i = 1; i <= K; ++i) {
			int R = n / (i + 1) + 1;
			if(n / i != i) pairs += n - n % i;
			pairs += i * soma(R, r[i - 1] - 1);
			r[i] = R;
		}
		pairs = m - pairs;
		long long g = __gcd(pairs, m);
		cout << pairs / g << '/' << m / g << '\n';
	}
    return 0;
}