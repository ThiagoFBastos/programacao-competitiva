#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 200, max_buckets = 317;

int t[maxn], p[maxn], chuncks, chunck_size, bPos[maxn], color_max[max_buckets], color_min[max_buckets], N, K, T;

void update(int, int, int);

void update(int L, int R, int dia) {

	int bL, bR;

	bL = bPos[L];
	bR = bPos[R];

	if(color_min[bL] == -1) {
		int LR = min(R + 1, (bL + 1) * chunck_size);
		for(int k = L; k < LR; ++k) {
			if(dia - t[k] > T)
				++p[k], --p[k + 1];
			t[k] = dia;
		}
	} else if(dia - color_max[bL] > T)
		++p[bL * chunck_size], --p[(bL + 1) * chunck_size];
	else {
		int LL = bL * chunck_size;
		int RR = LL + chunck_size;
		int LR = min(R + 1, RR);
		for(int k = LL; k < L; ++k) {
			if(color_min[bL] - t[k] > T)
				++p[k], --p[k + 1];
			t[k] = color_max[bL];
		}
		for(int k = L; k < LR; ++k) {
			if(color_min[bL] - t[k] > T)
				++p[k], --p[k + 1];
			t[k] = dia;
		}
		for(int k = LR; k < RR; ++k) {
			if(color_min[bL] - t[k] > T)
				++p[k], --p[k + 1];
			t[k] = color_max[bL];
		}
		color_min[bL] = color_max[bL] = -1;
	}
	
	if(bL != bR) {
		if(color_min[bR] == -1) {
			for(int k = bR * chunck_size; k <= R; ++k) {
				if(dia - t[k] > T) 
					++p[k], --p[k + 1];
				t[k] = dia;
			}
		} else if(dia - color_max[bR] > T)
			++p[bR * chunck_size], --p[(bR + 1) * chunck_size];
		else {
			int RL = bR * chunck_size, RR = (bR + 1) * chunck_size;
			for(int k = RL; k <= R; ++k) {
				if(color_min[bR] - t[k] > T)
					++p[k], --p[k + 1];
				t[k] = dia;
			}
			for(int k = R + 1; k < RR; ++k) {
				if(color_min[bR] - t[k] > T)
					++p[k], --p[k + 1];
				t[k] = color_max[bR];
			}
			color_min[bR] = color_max[bR] = -1;
		}
	}

	for(int k = bL + 1; k < bR; ++k) {
		if(color_min[k] == -1)
			color_min[k] = color_max[k] = dia;
		else if(dia - color_max[k] > T)
			++p[k * chunck_size], --p[(k + 1) * chunck_size];
		else
			color_max[k] = dia;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	while(cin >> N >> K >> T) {

		chunck_size = 1 + (int)sqrt(N);
		chuncks = (N + chunck_size - 1) / chunck_size;

		for(int i = 0; i <= N; ++i) {
			t[i] = p[i] = 0;
			bPos[i] = i / chunck_size;
		}

		for(int i = 0; i < chuncks; ++i)
			color_min[i] = color_max[i] = -1;

		for(int k = 1; k <= K; ++k) {
			int L, R;
			cin >> L >> R;
			update(L - 1, R - 1, k);
		}

		for(int k = 0; k < chuncks; ++k) {
			if(color_min[k] == -1) 
				continue;		
			int L = k * chunck_size;
			int R = L + chunck_size;
			while(L < R) {
				if(color_min[k] - t[L] > T)
					++p[L], --p[L + 1];
				t[L++] = color_max[k];
			}
		}
		for(int k = 0; k < N; ++k) {
			if(K + 1 - t[k] > T)
				++p[k], --p[k + 1];
		}

		for(int k = 1; k < N; ++k) 
			p[k] += p[k - 1];

		vector<int> plantas;

		for(int i = 0; i < N; ++i) {
			if(p[i] == 0)
				plantas.push_back(i + 1);
		}
		cout << plantas.size();
		for(int x : plantas) cout << ' ' << x;
		cout << '\n';
	}

	return 0;
}