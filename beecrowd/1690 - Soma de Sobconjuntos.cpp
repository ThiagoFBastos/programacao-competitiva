#include <bits/stdc++.h>
using namespace std;
void read(int& n) {
	register int ch = getchar_unlocked();
	while(ch < 48) ch = getchar_unlocked();
	n = 0;
	while(ch > 47) {
		n = 10 * n + ch - '0';
		ch = getchar_unlocked();
	}
}
int main() {
	const int MAXN = 1e4;
	int a[MAXN], t;
	long long p[MAXN];
	read(t);
	while(t--) {
		int n;
		read(n);
		for(int i = 0; i < n; ++i) read(a[i]);
		sort(a, a + n);
		if(a[0] != 1) puts("1");
		else {
			long long res = 0;
			p[0] = 1;
			for(int i = 1; i < n; ++i) {
				if(p[i - 1] < a[i] - 1) {
					res = p[i - 1] + 1;
					break;
				}
				p[i] = p[i - 1] + a[i];
			}
			if(res) printf("%lld\n", res);
			else printf("%lld\n", p[n - 1] + 1);
		}
	}
	return 0;
}
