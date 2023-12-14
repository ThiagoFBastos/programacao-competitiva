#include "xylophone.h"
#include <bits/stdc++.h>
 
using namespace std;
 
void solve(int N) {
 
	int l = 1, r = N + 1;
 
	while(l < r) {
		int m = (l + r) / 2;
		if(query(m, N) != N - 1) r = m;
		else l = m + 1;
	}
 
	int k = r - 1;
 
	vector<int> P(N + 1, -1);
	vector<bool> vis(N + 1, false);
 
	P[k] = 1;
	P[k + 1] = 1 + query(k, k + 1);
	
	vis[1] = vis[P[k + 1]] = true;
 
	auto f = [&](int l, int r, int i) {
		int d2 = query(min(l,i), max(l,i));
		int lo = P[l] - d2, hi = P[l] + d2;
		
		if(lo > 0 && hi <= N && !vis[lo] && !vis[hi]) {
			int d = query(min({l,r,i}), max({l,r,i}));
 
			if(d == abs(P[l] - P[r]))
				P[i] = P[l] > P[r] ? P[l] - d2 : P[l] + d2;
			else {
				int lo = min(P[l], P[r]) + d, hi = max(P[l], P[r]) - d;
				if(lo <= N && hi >= 1 && !vis[lo] && !vis[hi])
					P[i] = P[l] > P[r] ? (P[l] + (d == d2 ? -d : d2)) : (P[l] + (d == d2 ? d : -d2));
				else
					P[i] = lo > N || vis[lo] ? hi : lo;
			}
		} else
			P[i] = lo > 0 && !vis[lo] ? lo : hi;
 
		vis[P[i]] = true;
	};
 
	for(int i = k + 2; i <= N; ++i) f(i - 1, i - 2, i);
	for(int i = k - 1; i; --i) f(i + 1, i + 2, i);
	for(int i = 1; i <= N; ++i) answer(i, P[i]);
}
