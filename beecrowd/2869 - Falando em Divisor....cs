using System; 

class URI {

    static void Main(string[] args) { 

        
		const double inf = 1e9;
		const int N = 101;
		const int MOD = (int)(1e9 + 7);
		
		int t = int.Parse(Console.ReadLine());
		
		int[] primes = new int[6] {2, 3, 5, 7, 11, 13};
		double[] dp = new double[N];
		int[] mod = new int[N];
		
		for(; t > 0; --t) {
			
			int n = int.Parse(Console.ReadLine());
			
			for(int i = 0; i <= n; ++i) {
				dp[i] = inf;
				mod[i] = 0;
			}
			
			dp[1] = 0;
			mod[1] = 1;
			
			foreach(int p in primes) {
				for(int k = n; k > 0; --k) {
					int mod_pow = 1;
					
					for(int i = 1; k * i <= n; ++i) {
						double new_dp = dp[k] + (i - 1) * Math.Log(p);
						
						if(dp[k * i] > new_dp) {
							dp[k * i] = new_dp;
							mod[k * i] = (int)((long)mod[k] * mod_pow % MOD);
						}
						
						mod_pow =  (int)((long)mod_pow * p % MOD);
					}
				}
			}
			
			Console.WriteLine(mod[n]);
		}
    }
}