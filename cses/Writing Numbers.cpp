#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ull max_digit_count(ll n) {
	ull f[10] = {0};
	ull p = 1, m = 1;
	int k = 0, digit;
	while(n > 0) {
		digit = n % 10;
		f[digit] += m;
		for(int d = 0; d < digit; ++d) f[d] += p;
		for(int d = 0; d < 9; ++d) f[d] += digit * (p / 10) * k;
		m += p * digit;
		n /= 10;
		p *= 10;
		++k;
	}
	f[0] -= p / 10; 
	return *max_element(f, f + 10);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll n, low = 9, high = 1e18 + 1;
	cin >> n;
	while(low < high) {
		ll mid = (low + high) >> 1;
		if(max_digit_count(mid) > n) high = mid;
		else low = mid + 1;
	}
	cout << high - 1 << '\n';
    return 0;
}
