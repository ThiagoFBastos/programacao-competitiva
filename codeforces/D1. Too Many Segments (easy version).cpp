#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

#define MAXN 200

struct segmento {
	
	int l, r, k;
};

bool operator<(segmento s1, segmento s2) {
	return s1.l < s2.l || (s1.r > s2.r && s1.l == s2.l);
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, k;

	cin >> n >> k;

	int c[MAXN + 1];

	memset(c, 0, sizeof c);

	vector<segmento> seg(n);

	for(int k = 0; k < n; ++k) {

		cin >> seg[k].l >> seg[k].r;

		seg[k].k = k + 1;

		for(int i = seg[k].l; i <= seg[k].r; ++i)
			++c[i];
	}

	sort(seg.begin(), seg.end());

	vi d; 
	vector<bool> used(n, 0);

	for(int i = 1; i <= MAXN; ++i) {

		while(c[i] > k) {

			int r = 0, h = 0;
	
			for(int j = 0; j < n && seg[j].l <= i; ++j) {

				if(!used[j] && seg[j].l <= i && seg[j].r >= i && seg[j].r > r)
					r = seg[j].r, h = j;
			}

			d.push_back(seg[h].k);

			used[h] = true;

			for(int j = i; j <= seg[h].r; ++j)
				--c[j];
		}
	}

	cout << d.size() << '\n';
	for(int k = 0; k < (int)d.size() - 1; ++k) cout << d[k] << ' ';
	if(d.size()) cout << d.back() << '\n';

	return 0;
}