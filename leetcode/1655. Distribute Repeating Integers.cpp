#include "bits/stdc++.h"
 
using namespace std;
 
using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        
        array<int, 50> cnt;
        
        auto p = nums;
        sort(p.begin(), p.end());
        p.resize(unique(p.begin(), p.end()) - p.begin());
        
        cnt.fill(0);
        
        for(int x : nums) {
        	x = lower_bound(p.begin(), p.end(), x) - p.begin();
        	++cnt[x];
        }
  
    	int n = quantity.size(), m = p.size();
    	
    	vector<bool> dp(1 << n, false);
    	vector<int> peso(1 << n, 0);
    	
    	for(int k = 1; k < (1 << n); ++k) peso[k] = quantity[__builtin_ctz(k)] + peso[k ^ (k & -k)];
    	
    	dp[(1 << n) - 1] = true;
    	
    	for(int i = 0; i < m; ++i)
    		for(int k = 0; k < (1 << n); ++k)
    			for(int S = k; S; S = (S - 1) & k) dp[k ^ S] = dp[k ^ S] || dp[k] && peso[S] <= cnt[i];
    	
    	return dp[0];
    }
};