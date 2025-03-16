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
typedef long double ld;


int n, q, n_chuncks, chunck_sz, **chuncks, *bPos;
ll *a, *chunck_ans, *color;

ll query(int, int);
void upd(int, int, int);

ll query(int L, int R) {
	int bL = bPos[L], bR = bPos[R], LR, LL;
	ll ans = 0;

	LL = bL * chunck_sz;
	LR = LL + chunck_sz;

	if(color[bL]) {
		for(int k = LL; k < LR; ++k) 
			a[k] ^= color[bL];
		color[bL] = 0;
	}

	LR = min(LR, R + 1);

	for(int k = L; k < LR; ++k)
		ans += a[k];

	if(bL != bR) {
		int RL = bR * chunck_sz;
		if(color[bR]) {
			int RR = RL + chunck_sz;
			for(int k = RL; k < RR; ++k) 
				a[k] ^= color[bR];
			color[bR] = 0;
		}
		for(int k = RL; k <= R; ++k) 
			ans += a[k];
	}

	for(int k = bL + 1; k < bR; ++k)
		ans += chunck_ans[k];
	return ans;
}

void upd(int L, int R, int bit) {
	int bL = bPos[L], bR = bPos[R], LR, LL;
	ll mask = 1LL << bit;

	LL = bL * chunck_sz;
	LR = LL + chunck_sz;

	if(color[bL]) {
		for(int k = LL; k < LR; ++k) 
			a[k] ^= color[bL];
		color[bL] = 0;
	}
	
	LR = min(LR, R + 1);

	for(int k = L; k < LR; ++k) {
		if(a[k] & mask) {
			chunck_ans[bL] -= mask;
			--chuncks[bL][bit];
		}
		else {
			++chuncks[bL][bit];
			chunck_ans[bL] += mask;
		}
		a[k] ^= mask;
	}

	if(bL != bR) {
		int RL, RR;

		RL = bR * chunck_sz;
		RR = RL + chunck_sz;

		if(color[bR]) {
			for(int k = RL; k < RR; ++k) 
				a[k] ^= color[bR];
			color[bR] = 0;
		}

		for(int k = RL; k <= R; ++k) {
			if(a[k] & mask) {
				chunck_ans[bR] -= mask;
				--chuncks[bR][bit];
			}
			else {
				chunck_ans[bR] += mask;
				++chuncks[bR][bit];
			}
			a[k] ^= mask;
		}
	}

	for(int k = bL + 1; k < bR; ++k) {
		chunck_ans[k] += (chunck_sz - 2LL * chuncks[k][bit]) << bit;
		chuncks[k][bit] = chunck_sz - chuncks[k][bit];
		color[k] ^= mask;
	}
	
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	
	chunck_sz = 1 + (int)sqrt(n);
	n_chuncks = (n + chunck_sz - 1) / chunck_sz;

	chuncks = new int*[n_chuncks];
	color = new ll[n_chuncks];
	chunck_ans = new ll[n_chuncks];
	a = new ll[n + chunck_sz];
	bPos = new int[n + chunck_sz];

	for(int i = 0; i < n_chuncks; ++i) {
		chuncks[i] = new int[64];
		color[i] = chunck_ans[i] = 0;
		for(int k = 0; k < 64; ++k)
			chuncks[i][k] = 0;
	}

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		bPos[i] = i / chunck_sz;
		chunck_ans[bPos[i]] += a[i];
		for(int k = 0; k < 64; ++k)
			chuncks[bPos[i]][k] += (a[i] & 1LL << k) != 0;
	}
	
	cin >> q;

	while(q--) {
		string s;
		int L, R, k;
		cin >> s >> L >> R;
		if(toupper(s[0]) == 'S')
			cout << query(L, R) << '\n';
		else {
			cin >> k;
			upd(L, R, k);
		}
	}

	return 0;
}