#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,avx,avx2")
#define MAXN 10000000
using namespace std;
bool is_even(int C, int K) {
	while(K > 0) {
		if((K & 1) > (C & 1)) return true;
		K >>= 1;
		C >>= 1;
	}
	return false;
}
int main() {
	ios_base :: sync_with_stdio(false); 
	cin.tie(0);
	cout.tie(0);
	bitset<MAXN + 1> S;
	int a, b, cnt = 0;
	cin >> a >> b;
	if(a > b) swap(a, b);
	if(a == b) cout << "?\n";
	else {
		S.set();
		S[0] = S[1] = 0;
		for(unsigned k = 4; k <= b; k += 2) S[k] = 0;
		for(unsigned k = 3; k <= b; ++k)
			if(S[k]) for(unsigned i = 2 * k; i <= b; i += k) S[i] = 0;
		for(int k = a; k <= b; ++k) cnt += S[k];
		if(is_even(b - a + cnt - 1, b - a)) cout << "Bob\n";
		else cout << "Alice\n";
	}
	return 0;
}