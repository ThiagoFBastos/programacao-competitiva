using System; 

class URI {

	static int min(int a, int b) {
		return a < b ? a : b;	
	}
	
	static int max(int a, int b) {
		return a > b ? a : b;	
	}
	
    static void Main(string[] args) { 
        const int N = (int)(1e3 + 10);
		int[,] dp = new int[N, N];
		int[] a = new int[N];
		
		
		while(true) {
			int n = int.Parse(Console.ReadLine());
			
			if(n == 0) break;
			
			var s = Console.ReadLine().Split(' ');
			int even = 0;
		
			n <<= 1;
			
			for(int i = 0; i < n; ++i) {
				a[i] = 1 - int.Parse(s[i]) % 2;
				even += a[i];
			}
		
			for(int i = 0; i < n; ++i)
				dp[i, i] = -a[i];
			
			for(int l = 2; l <= n; ++l) {
				for(int i = 0; i + l <= n; ++i) {
					int j = i + l - 1;
					if(l % 2 == 1)
						dp[i, j] = min(dp[i + 1, j] - a[i], dp[i, j - 1] - a[j]);
					else
						dp[i, j] = max(dp[i + 1, j] + a[i], dp[i, j - 1] + a[j]);
				}
			}
			
			Console.WriteLine((even + dp[0, n - 1]) / 2);
		}
    }

}