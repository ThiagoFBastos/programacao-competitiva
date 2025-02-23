using System; 
using System.Collections.Generic;

class URI {

	struct Vertex {
		public int v;
		public int degree;
	}

	static int cmp(Vertex a, Vertex b) {
		return b.degree - a.degree;
	}

    static void Main(string[] args) {
		while(true) {

			var l = Console.ReadLine().Split(' ');

			int n = int.Parse(l[0]);
			int m = int.Parse(l[1]);

			if(n + m == 0) break;
	
			Vertex[] S = new Vertex[n];
			int[] preSum = new int[n + 1];

			for(int i = 0; i < n; ++i) {
				S[i].v = i;
				S[i].degree = 0;
			}
			
			for(int i = 0; i < m; ++i) {
				var ll = Console.ReadLine().Split(' ');
				int u = int.Parse(ll[0]) - 1, v = int.Parse(ll[1]) - 1;
				++S[u].degree;
				++S[v].degree;	
			}

			Array.Sort(S, cmp);

			for(int i = 1; i <= n; ++i) preSum[i] = preSum[i - 1] + S[i - 1].degree;

			bool flag = false;

			for(int i = 1; i <= n; ++i)
				flag = flag || preSum[i] == i * (i - 1) + preSum[n] - preSum[i];

			Console.WriteLine(flag ? "Y" : "N");
		}						
    }	
}