using System; 

class URI {

    const int N = 3;
    
    static void mul(int[,] a, int[,] b, int MOD) {
        int[,] c = new int[N, N];
        
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                c[i, j] = 0;
                
                for(int k = 0; k < N; ++k)
                    c[i, j] = (int)(c[i, j] + (long)a[i, k] * b[k, j]) % MOD;
            }
        }
        
        for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            a[i, j] = c[i, j];
    }
    
    static void modPow(int[,] dest, int[,] src, long p, int MOD) {
        for(int i = 0; i < N; ++i)
        for(int j = 0; j < N; ++j)
            dest[i, j] = i == j ? 1 : 0;
            
        for(; p > 0; p >>= 1) {
            if(p % 2 == 1)
                mul(dest, src, MOD);
                
            mul(src, src, MOD);
        }
    }
    
    public static void Main(string[] args)
    {
       int caso = 1;
       
       while(true) {
           long n;
           int b;
		   
           int[,] T = new int[N, N];
           int[,] A = new int[N, N];
           
           var line = Console.ReadLine().Split(' ');
           
           n = long.Parse(line[0]);
           b = int.Parse(line[1]);
           
		   if(n == 0 && b == 0) break;
		   
		   else if(n < 2) {
			   Console.WriteLine("Case {0}: {1} {2} 1", caso, n, b);
			   ++caso;
			   continue;
		   }
		   
           A[0, 0] = 1;
		   A[0, 1] = 1;
		   A[0, 2] = 1;
		   
		   A[1, 0] = 1;
		   A[1, 1] = 0;
		   A[1, 2] = 0;
		   
		   A[2, 0] = 0;
		   A[2, 1] = 0;
		   A[2, 2] = 1;
		   
		   modPow(T, A, n - 1, b);
		   
		   Console.WriteLine("Case {0}: {1} {2} {3}", caso, n, b, (T[0, 0] + T[0, 1] + T[0, 2]) % b);
		   ++caso;
       }
    }

}