#include "ricehub.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
 
int besthub(int R, int L, int X[], long long B)
{
  int ans = 0;  
  std :: vector<long long> pre(R + 1, 0);
  for(int i = 1; i <= R; ++i) pre[i] = pre[i - 1] + X[i - 1];
  for(int i = 0; i < R; ++i) {
	 int lo = 0;
	 for(int k = 31 - __builtin_clz(R); k >= 0; --k) {
		int n = lo | (1 << k);
		int mid = (n - 1) / 2;
		if(i - mid < 0 || i + mid >= R) continue;
		auto l = pre[i] - pre[i - mid];
		auto r = pre[i + mid + 1] - pre[i + 1];
		if(n & 1) {
			if(r - l <= B) lo = n;
		} else {
			if(i + mid + 1 < R && r + X[i + mid + 1] - l - X[i] <= B) lo = n;
			if(i - mid - 1 >= 0 && r - l - X[i - mid - 1] + X[i] <= B) lo = n;
		}
	 }
	 ans = std :: max(ans, lo);
  }
  return ans;
}
