#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 200, max_buckets = 317;

int L, C, N, n_buckets, sz_bucket, a[maxn], cnt[maxn], cor[max_buckets], bPos[maxn], bucket[max_buckets][maxn];

int query(int);

void update(int, int, int);

int query(int P) {
	int l = 0, r = L - 1;
	int bL = bPos[l], bR = bPos[r];
	int cL = cor[bL], cR = cor[bR], S = 0;
	int LR = min(L, bL * sz_bucket + sz_bucket);

	if(cL == -1) {
		for(int k = l; k < LR; ++k)
			if(a[k] == P) ++S;
	} else if(cL == P)
		S += LR - l;
	
	if(bL != bR) {
		int RL = bR * sz_bucket;
		if(cR == -1) {
			for(int k = RL; k <= r; ++k)
				if(a[k] == P) ++S;
		} else if(cR == P)
			S += r - RL + 1;
	}

	for(int k = bL + 1; k < bR; ++k) {
		if(cor[k] == -1) S += bucket[k][P];
		else if(cor[k] == P) S += sz_bucket;
	}

	return S;
}

void update(int L, int R, int X) {

	int bL = bPos[L], bR = bPos[R];
	int cL = cor[bL], cR = cor[bR];
	int LR = min(R + 1, bL * sz_bucket + sz_bucket);

	if(cL == -1) {

		bucket[bL][X] += LR - L;

		for(int k = L; k < LR; ++k) {
			--bucket[bL][a[k]];
			a[k] = X;
		}

	} else {
		int LL = bL * sz_bucket, LRF = bL * sz_bucket + sz_bucket;

		for(int k = LL; k < L; ++k) {
			--bucket[bL][a[k]];
			a[k] = cL;
		}

		for(int k = L; k < LR; ++k) {
			--bucket[bL][a[k]];
			a[k] = X;
		}

		for(int k = LR; k < LRF; ++k) {
			--bucket[bL][a[k]];
			a[k] = cL;
		}

		bucket[bL][cL] += L - LL + LRF - LR;
		bucket[bL][X] += LR - L;
		cor[bL] = -1;
	}

	if(bL != bR) {
		int RL = bR * sz_bucket;
		if(cR == -1) {
			bucket[bR][X] += R - RL + 1;
			for(int k = RL; k <= R; ++k) {
				--bucket[bR][a[k]];
				a[k] = X;
			}
		} else {

			int RR = RL + sz_bucket;

			bucket[bR][X] += R - RL + 1;
			bucket[bR][cR] += RR - R - 1;

			for(int k = RL; k <= R; ++k) {
				--bucket[bR][a[k]];
				a[k] = X;
			}

			for(int k = R + 1; k < RR; ++k) {
				--bucket[bR][a[k]];
				a[k] = cR;
			}

			cor[bR] = -1;
		}
	}
	
	for(int k = bL + 1; k < bR; ++k)
		cor[k] = X;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> L >> C >> N;
	
	sz_bucket = 1 + (int)sqrt(L);
	n_buckets = (L + sz_bucket - 1) / sz_bucket;
	
	for(int k = 0; k < n_buckets; ++k) {
		cor[k] = 1;
		for(int i = 0; i <= C; ++i)
			bucket[k][i] = 0;
	}
	
	memset(a, 0, sizeof a);

	for(int k = 0; k < L; ++k)
		bPos[k] = k / sz_bucket;

	while(N--) {

		int P, X, A, B, S, M1, M2;

		cin >> P >> X >> A >> B;

		S = query(P);
		M1 = (A + 1LL * S * S) % L;
		M2 = (A + (S + B + 0LL) * (S + B)) % L;
		
		update(min(M1, M2), max(M2, M1), X);
	}

	memset(cnt, 0, (C + 1) * sizeof(int));

	for(int k = 0; k < n_buckets; ++k) {
		if(cor[k] == -1) 
			continue;
		int L = k * sz_bucket;
		int R = L + sz_bucket;
		while(L < R)
			a[L++] = cor[k];
	}

	for(int k = 0; k < L; ++k)
		++cnt[a[k]];

	cout << *max_element(cnt, cnt + C + 1) << '\n';
	return 0;
}