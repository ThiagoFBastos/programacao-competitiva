using System; 
using System.Collections.Generic;

class UF {
	private int[] par;
	private int[] rank;
	private int[] sz;

	public UF(int n) {
		par = new int[n];
		rank = new int[n];
		sz = new int[n];
	
		for(int i = 0; i < n; ++i) {
			par[i] = i;
			sz[i] = 1;
		}
	}

	private int findSet(int u) {
		return u == par[u] ? u : par[u] = findSet(par[u]);
	}

	public void join(int u, int v) {
		u = findSet(u);
		v = findSet(v);
		if(u == v) return;
		else if(rank[u] > rank[v]) {
			u ^= v;
			v ^= u;
			u ^= v;
		}
		par[u] = v;
		rank[v] += rank[u] == rank[v] ? 1 : 0;
		sz[v] += sz[u];		
	}

	public int nodes(int u) {
		return sz[findSet(u)];
	}
}

class URI {
    static void Main(string[] args) {
		while(true) {
			int n = int.Parse(Console.ReadLine());

			if(n == 0) break;

			var l = Console.ReadLine().Split(' ');

			UF uf = new UF(2 * n + 1);
			var mp = new SortedDictionary<int, int>();
			int id = 1;
			
			mp[1] = 0;

			foreach(string s in l) {
				var ll = s.Substring(1, s.Length - 2).Replace(',', ' ').Split(' ');
				int u = int.Parse(ll[0]);
				int v = int.Parse(ll[1]);
				if(!mp.ContainsKey(u)) mp[u] = id++;
				if(!mp.ContainsKey(v)) mp[v] = id++;
				uf.join(mp[u], mp[v]);
			}

			Console.WriteLine(uf.nodes(0));
		}					
    }	
}