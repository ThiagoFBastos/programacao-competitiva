#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string dna;
	int lo = 0, hi = 0, maxl = 0;
	cin >> dna;
	while(hi <= dna.size()) {
		if(dna[lo] != dna[hi]) {
			maxl = max(maxl, hi - lo);
			lo = hi;
		}
		++hi;
	}
	cout << maxl << '\n';
	return 0;
} 
