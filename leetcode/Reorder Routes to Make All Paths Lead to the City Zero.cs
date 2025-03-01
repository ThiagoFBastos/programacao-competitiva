public class Edge {
    public int Destiny {get; set;}
    public bool Inverted {get; set;}
}

public class Solution {
    public int MinReorder(int n, int[][] connections) {
        var adj = new List<List<Edge>>(n);

        for(int i = 0; i < n; ++i)
            adj.Add(new List<Edge>());

        foreach(var e in connections) {
            int from = e[0], to = e[1];
            adj[from].Add(new Edge() {Destiny = to, Inverted = false});
            adj[to].Add(new Edge() {Destiny = from, Inverted = true});
        }

        Queue<int> q = new Queue<int>();
        bool[] visited = new bool[n];
        int result = 0;

        visited[0] = true;
        q.Enqueue(0);

        while(q.Count > 0) {
            int a = q.Dequeue();

            foreach(var edge in adj[a]) {
                int b = edge.Destiny;
                bool status = edge.Inverted;

                if(!visited[b]) {
                    visited[b] = true;
                    q.Enqueue(b);
                    if(!status)
                        ++result;
                }
            }
        }

        return result;
    }
}