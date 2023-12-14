#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);	
	cout.tie(0);
	const int MAXN = 2e5;
	int n, p[MAXN + 1];
	set<int> S[30];
	cin >> n;
	p[0] = 0;
	for(int i = 0; i < n; ++i) {
		int a;
		cin >> a;
		p[i + 1] = p[i] ^ a;
	}
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		int r = 0x20000000;
		for(int k = 29; k >= 0; --k) {
			if(!(p[i] & r) && !S[k].empty()) {
				int mask = r;
				for(int j = k - 1; j >= 0; --j) {
					set<int> :: iterator next;
					r >>= 1;
					if(p[i] & r) {
						next = S[k].lower_bound(mask);
						if(*next & r) mask |= r;
					}
					else {
						int x = mask | r;
						next = S[k].lower_bound(x);
						if(next != S[k].end() && (*next & ~(r - 1)) == x) mask = x;
					}
				}
				res = max(res, mask ^ p[i]);
				break;
			}
			r >>= 1;
		}
		res = max(res, p[i]);
		if(p[i]) S[31 - __builtin_clz(p[i])].insert(p[i]);
	}
	cout << res << '\n';
	return 0;
}
