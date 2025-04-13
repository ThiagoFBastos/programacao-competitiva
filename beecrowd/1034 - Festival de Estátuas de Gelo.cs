using System; 

class URI {
   
	static int min(int a, int b)
	{
		return a < b ? a : b;	
	}
	
    public static void Main(string[] args)
    {
		const int N = 10101;
		const int INF = (int)1e9;
		
       int t = int.Parse(Console.ReadLine());
	   int[] dp = new int[N];
		
	   for(; t > 0; --t) 
	   {
		   var l = Console.ReadLine().Split(' '); 
		   int n = int.Parse(l[0]);
		   int m = int.Parse(l[1]);
		   
		   int[] v = new int[n];
		   
		   var a = Console.ReadLine().Split(' ');
		   
		   for(int i = 0; i < n; ++i) v[i] = int.Parse(a[i]);
			   
		   Array.Sort(v);
		   
		   int M = min(m, 100 * v[n - 1] + m % v[n - 1]);
		   
		   for(int j = 0; j <= M; ++j)
			   dp[j] = INF;
		   
		   dp[M] = 0;
		   
		   foreach(int x in v)
			   for(int k = M; k >= x; --k)
					dp[k - x] = min(dp[k - x], dp[k] + 1);
		   
		   Console.WriteLine(dp[0] + (m - M) / v[n - 1]);
	   }
    }
}