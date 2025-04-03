using System; 

class URI {
    
	static Tuple<int, int>[][] adj;
	static int[] minW;
	
	static void dfs(int u, int p = -1)
	{
		if(p < 0) minW[u] = int.MaxValue;
		
		foreach(Tuple<int, int> e in adj[u])
		{
			int v = e.Item1, w = e.Item2;
			if(v == p) continue;
			minW[v] = minW[u] < w ? minW[u] : w;
			dfs(v, u);
		}
	}
	
	public static void Main()
	{
		int n = int.Parse(Console.ReadLine());
		
		if(n == 1)
		{
			return;
		}
		
		int[] deg = new int[n];
		var edges = new Tuple<int, int, int>[n - 1];
		
		for(int i = 0; i < n - 1; ++i)
		{
			var l = Console.ReadLine().Split(' ');	
			int u = int.Parse(l[0]) - 1, v = int.Parse(l[1]) - 1, w = int.Parse(l[2]);
			edges[i] = Tuple.Create(u, v, w);
			++deg[u];
			++deg[v];
		}
		
		adj = new Tuple<int, int>[n][];
		minW = new int[n];
		
		for(int i = 0; i < n; ++i) adj[i] = new Tuple<int, int>[deg[i]];
		
		for(int i = 0; i < n - 1; ++i)
		{
			int u = edges[i].Item1, v = edges[i].Item2, w = edges[i].Item3;
			adj[u][--deg[u]] = Tuple.Create<int, int>(v, w);
			adj[v][--deg[v]] = Tuple.Create<int, int>(u, w);
		}
		
		dfs(n - 1);
		
		for(int i = 0; i < n - 1; ++i)
		{
			Console.Write(minW[i]);
			Console.Write(i == n - 2 ? '\n' : ' ');
		}
	}
}