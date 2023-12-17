#include "cave.h"

const int MAXN = 5000;
 
int S[MAXN], D[MAXN], marked[MAXN];
 
void exploreCave(int N) {

	for(int i = 0; i < N; ++i) {
		S[i] = 0;
		marked[i] = 1;
	}
	
	for(int i = 0; i < N; ++i) {
		if(tryCombination(S) != i) {
			for(int j = 0; j < N; ++j) S[j] ^= marked[j];
		}
		
		int lo = 0, hi = N - 1;
		
		while(lo < hi) {
			int mid = (lo + hi) >> 1;
			
			for(int j = 0; j <= mid; ++j) S[j] ^= marked[j];
			
			int ans = tryCombination(S);
			
			if(ans != i) hi = mid;
			else lo = mid + 1;
			
			for(int j = 0; j <= mid; ++j) S[j] ^= marked[j];
		}
		
		D[hi] = i;
		S[hi] ^= 1;
		marked[hi] = 0;
	}
	
	answer(S, D);
}
