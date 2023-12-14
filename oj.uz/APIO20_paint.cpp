#include "paint.h"
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define INF 1000000000
#define pb push_back
#define rall(x) x.rbegin(),x.rend()
 
using ii = pair<int, int>;
 
int minimumInstructions(int N, int M, int K,vector<int> C,vector<int> A,vector<std::vector<int>> B) {
	
	vector<vector<int>> match(K);
	vector<int> time_(M, N), cur(M, 0), tcur(M);
 
	for(int i = 0; i < M; ++i)
		for(int c : B[i])
			match[c].pb(i);
 
	vector<int> st(2 * N + 2, INF);
 
	auto query = [&](int l, int r) {
		int ans = INF;
		l += N, r += N;
		for(; l <= r; l /= 2, r /= 2) {
			if(l & 1) ans = min(ans, st[l++]);
			if(~r & 1) ans = min(ans, st[r--]);
		}
		return ans;
	};
 
	auto upd = [&](int k, int x) {
		k += N;
		st[k] = x;
		for(k /= 2; k; k /= 2) st[k] = min(st[2 * k], st[2 * k + 1]);
	};
 
	upd(N, 0);
 
	int dp = 0;
 
	for(int i = N - 1; i >= 0; --i) {
		int jump = 0;
 
		for(int j : match[C[i]]) {
			int k = j + 1;
			if(k >= M) k -= M;
			if(time_[k] > i + 1) cur[k] = 0;
			cur[k] = min(cur[k], M - 1);
			tcur[j] = 1 + cur[k];
			jump = max(jump, tcur[j]);
		}
		
		for(int j : match[C[i]]) time_[j] = i;
 
		swap(tcur, cur);
 
		if(jump == M || jump >= N - i) {
			dp = query(i + 1, min(N, i + jump)) + 1;
			upd(i, dp);
		} else
			dp = INF;
	}
			
	return dp > N ? -1 : dp;
}
