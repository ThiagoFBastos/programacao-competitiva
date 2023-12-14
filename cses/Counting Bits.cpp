#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	long long n, ones = 0, r = 1, p = 1;
	int k = 0;
	cin >> n;
	while(n > 0) {
		if(n & 1) ones += r + (p >> 1) * k;
		++k;
		r += (n & 1) * p; 
		p <<= 1;
		n >>= 1;
	}
	cout << ones << '\n';
	return 0;
}
