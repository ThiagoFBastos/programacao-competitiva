public class Solution {
    public int MinDistance(string word1, string word2) {
        const int INF = 1000000000;
        int n = word1.Length, m = word2.Length;
        int[,] dp = new int[n+2,m+2];

        for(int i = 0; i <= n; ++i)
            for(int j = 0; j <= m; ++j)
                dp[i,j] = INF;

        dp[0,0] = 0;

        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= m; ++j) {
                dp[i+1,j+1] = int.Min(dp[i+1,j+1], dp[i,j] + (i<n&&j<m&&word1[i]==word2[j]?0:1));
                dp[i,j+1] = int.Min(dp[i,j+1], dp[i,j]+1);
                dp[i+1,j] = int.Min(dp[i+1,j], dp[i,j]+1);
            }
        }

        return dp[n,m];
    }
}