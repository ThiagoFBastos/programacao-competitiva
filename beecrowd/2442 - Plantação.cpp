#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;

typedef long long ll;
typedef unsigned long long ull;

vi a;
vector<char> t;
int F[101], p[101], cnt[101], nxt[101], n, k, L, f;
ll res = 0;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;

	a.resize(k);
	t.resize(n);
	memset(F, 0, sizeof F);
	memset(nxt, -1, sizeof nxt);

	for(int i = 0; i < k; ++i) {
		int a;
		cin >> a;
		++F[a];
	}

	for(int i = 100, r = -1; i >= 0; --i) {
		if(r != -1) nxt[i] = r;
		if(F[i]) r = i;
	}

	p[0] = cnt[0] = 0;
	
	for(int i = 1; i <= 100; ++i) {
		p[i] = p[i - 1] + F[i] * i;
		cnt[i] = cnt[i - 1] + F[i];
	}

	for(int i = 0; i < n; ++i)
		cin >> t[i];

	L = f = nxt[0];

	for(char tempo : t) {
		if(tempo == 'E') {
			if(f == 1) {
				int y = L;
				if(nxt[L] != -1) {
					L = nxt[L];
					f = f - y + L - 1; 
				}
				else break;
			} else --f;
		} else ++f;		
		res += p[100] - p[L - 1] + 1LL * (f - L) * (cnt[100] - cnt[L - 1]);
	}

	cout << res << '\n';

	return 0;
}