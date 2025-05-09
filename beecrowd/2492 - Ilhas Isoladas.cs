using System; 
using System.Collections.Generic;

class URI {
    static void Main(string[] args) {
		while(true) {
			int n = int.Parse(Console.ReadLine());

			if(n == 0) break;

			var mp = new SortedDictionary<string, int>();
			var inp = new string[n, 2];
			int id = 0;

			for(int i = 0; i < n; ++i) {
				var l = Console.ReadLine().Split(' ');
				inp[i, 0] = l[0];
				inp[i, 1] = l[2];
				if(!mp.ContainsKey(l[0])) mp[l[0]] = id++;
				if(!mp.ContainsKey(l[2])) mp[l[2]] = id++;
			}

			int m = mp.Count;

			var adj = new List<List<int>>(m);
			var inv = new List<List<int>>(m);

			for(int i = 0; i < m; ++i) {
				adj.Add(new List<int>());
				inv.Add(new List<int>());
			}

			for(int i = 0; i < n; ++i) {
				int u = mp[inp[i, 0]], v = mp[inp[i, 1]];
				adj[u].Add(v);
				inv[v].Add(u);
			}

			bool func = true;

			for(int u = 0; u < m; ++u)
			foreach(int v in adj[u])
				func = func && v == adj[u][0];

			if(!func) {
				Console.WriteLine("Not a function.");
				continue;
			}

			bool invertible = true;

			for(int u = 0; u < m; ++u)
				foreach(int v in inv[u])
					invertible = invertible && v == inv[u][0];

			Console.WriteLine(invertible ? "Invertible." : "Not invertible.");
		}				
    }
}