using System; 
using System.Collections.Generic;

class URI {

	class Path {
		public int par;
		public int v;
		public long cst;

		public Path(int par, int v, long cst) {
			this.par = par;
			this.v = v;
			this.cst = cst;
		}
	}
		
	class cmp : IComparer<Path> {
		private int sign(long x) {
			if(x < 0) return -1;
			else if(x > 0) return 1;
			return 0;
		}
		public int Compare(Path a, Path b) {
			if(a.cst != b.cst) return sign(a.cst - b.cst);
			if(a.par != b.par) return a.par - b.par;
			return a.v - b.v;
		}
	}
	
    static void Main(string[] args) {
		var st = new SortedSet<Path>(new cmp());
		var l = Console.ReadLine().Split(' ');

		int n = int.Parse(l[0]), m = int.Parse(l[1]);
		
		var adj = new List<List<Tuple<int, int>>>(n);
		var cost = new long[n, 2];

		for(int i = 0; i < n; ++i) {
			adj.Add(new List<Tuple<int, int>>());
			cost[i, 0] = cost[i, 1] = -1;
		}

		for(int i = 0; i < m; ++i) {
			l = Console.ReadLine().Split(' ');

			int a = int.Parse(l[0]) - 1, b = int.Parse(l[1]) - 1, c = int.Parse(l[2]);

			adj[a].Add(Tuple.Create(b, c));
			adj[b].Add(Tuple.Create(a, c));			
		}

		st.Add(new Path(0, 0, 0));

		while(st.Count > 0) {
			Path s = st.Min;

			int par = s.par, v = s.v;
			long cst = s.cst;

			st.Remove(st.Min);

			if(cost[v, par] != -1) continue;

			cost[v, par] = cst;

			foreach(Tuple<int, int> e in adj[v]) {
				int u = e.Item1, w = e.Item2;
				if(cost[u, par ^ 1] != -1) continue;
				st.Add(new Path(par ^ 1, u, w + cst));
			}
		}

		Console.WriteLine(cost[n - 1, 0]);
    }
}