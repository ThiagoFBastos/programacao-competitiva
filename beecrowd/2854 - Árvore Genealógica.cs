using System; 
using System.Collections.Generic;

class URI {

	static int[] par;
	static int[] rank;

	static void swap(ref int a, ref int b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}

	static int findSet(int u) {
		return u == par[u] ? u : par[u] = findSet(par[u]);
	}

	static bool join(int u, int v) {
		u = findSet(u);
		v = findSet(v);
		if(u == v) return false;
		if(rank[u] > rank[v]) swap(ref u, ref v);
		par[u] = v;
		if(rank[u] == rank[v]) ++rank[v];
		return true;
	}

    static void Main(string[] args) {
		var l = Console.ReadLine().Split(' ');

		int n = int.Parse(l[0]);
		int m = int.Parse(l[1]);
		
		var mp = new SortedDictionary<string, int>();

		par = new int[n];
		rank = new int[n];

		for(int i = 0; i < n; ++i) par[i] = i;

		for(int i = 0; i < m; ++i) {
			l = Console.ReadLine().Split(' ');
			if(!mp.ContainsKey(l[0])) mp[l[0]] = mp.Count;
			if(!mp.ContainsKey(l[2])) mp[l[2]] = mp.Count;
			if(join(mp[l[0]], mp[l[2]])) --n;
		}

		Console.WriteLine(n);
    }
}