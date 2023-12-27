#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
//#pragma GCC target ("sse,sse2,sse3,sse4,avx,avx2")
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define MAXN 200000
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, a[MAXN];
	ll op = 0;
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 1; i < n; ++i) {
		if(a[i] < a[i - 1]) {
			op += a[i - 1] - a[i];
			a[i] = a[i - 1];
		}
	}
	cout << op << '\n';
	return 0;
} 
