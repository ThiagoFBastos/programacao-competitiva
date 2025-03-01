public class UnionFind {
    private int[] parent;
    private int[] rank;

    public UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        for(int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    private int FindSet(int p) {
        if(parent[p] == p)
            return p;
        parent[p] = FindSet(parent[p]);
        return parent[p];
    }

    public bool Same(int u, int v) {
        return FindSet(u) == FindSet(v);
    }

    public void Join(int u, int v) {
        u = FindSet(u);
        v = FindSet(v);
        if(u == v) return;
        else if(rank[u] > rank[v]) {
            u ^= v; v ^= u; u ^= v;
        }
        parent[u] = v;
        rank[v] += rank[u] == rank[v] ? 1 : 0;
    }
}

public class Solution {
    public int FindCircleNum(int[][] isConnected) {
        int n = isConnected.Length;
        int provinces = n;
        UnionFind dsu = new UnionFind(n);

        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                if(isConnected[i][j] == 1 && !dsu.Same(i, j)) {
                    dsu.Join(i, j);
                    --provinces;
                }
            }
        }

        return provinces;
    }
}