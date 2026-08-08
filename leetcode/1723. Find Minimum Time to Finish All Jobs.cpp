const int inf = 1e9;

class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        
        int n = jobs.size();
        
        vector<int> job_sum(1 << n), dp(1 << n, inf);
        job_sum[0] = 0;
        
        for(int i = 1; i < (1 << n); ++i) job_sum[i] = job_sum[i ^ (i & -i)] + jobs[__builtin_ctz(i)];
     
        dp.back() = 0;
        
        for(int i = 0; i < k; ++i)
        	for(int j = 0; j < (1 << n); ++j)
        		for(int S = j; S; S = (S - 1) & j)
        			dp[S ^ j] = min(dp[S ^ j], max(job_sum[S], dp[j]));
        
        return dp[0];
    }
};