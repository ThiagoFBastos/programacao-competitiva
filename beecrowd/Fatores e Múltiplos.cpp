#include <bits/stdc++.h>

using namespace std;

/**
 * @brief This class finds the maximum matching of a bipartite graph in O(V^0.5 * E)
 */
class HopcroftKarp
{
public:
    /**
     * @brief HopcroftKarp constructor
     * @param n the number of nodes in the left side
     * @param m the number of nodes in the right side
     */
    HopcroftKarp(int m, int n):
        _adjU(m + 1),
        _pairU(m + 1),
        _pairV(n + 1),
        _dist(m + 1),
        _m(m),
        _n(n)
    {

    }

    /**
     * @brief Add an edge between u and v
     * @param u a vertex number that belongs to the interval [1, m]
     * @param v a vertex number that belongs to the interval [1, n]
     */
    void add_edge(int u, int v)
    {
        _adjU[u].emplace_back(v);
    }

    /**
     * @return The constant reference to the _pairU vector
     */
    const std::vector<int>& pairU() const 
    {
        return _pairU;
    }

    /**
     * @brief Find the maximum matching in the bipartite graph
     */
    int hopcroftKarp() 
    {
        int result = 0;

        while(bfs()) 
        {
            for(int u = 1; u <= _m; ++u) 
            {
                if(_pairU[u] == 0 && dfs(u)) 
                    ++result;
            }
        }

        return result;
    }

private:
    /**
     * @brief Run the bfs from the vertices of the left side
     * @return whether the graph has an augmenting path
     */
    bool bfs() 
    {
        std::queue<int> q;

        for(int u = 1; u <= _m; ++u) 
        {
            if(_pairU[u] == 0) 
            {
                _dist[u] = 0;
                q.push(u);
            } else 
                _dist[u] = INF;
        }

        _dist[0] = INF;
        
        while(!q.empty()) 
        {
            int u = q.front();

            q.pop();

            if(_dist[u] >= _dist[0]) 
                continue;

            for(int v : _adjU[u]) 
            {
                if(_dist[_pairV[v]] == INF) 
                {
                    _dist[_pairV[v]] = _dist[u] + 1;
                    q.push(_pairV[v]);
                }
            }
        }

        return _dist[0] != INF;
    }

    /**
     * @brief Find the matching edges
     * @param u the source vertex
     * @return whether from the source vertex exists an augmenting path
     */
    bool dfs(int u) 
    {
        if(!u) 
            return true;

        for(int v : _adjU[u]) 
        {
            if(_dist[_pairV[v]] == _dist[u] + 1) 
            {
                if(dfs(_pairV[v])) 
                {
                    _pairV[v] = u;
                    _pairU[u] = v;
                    return true;
                }
            }		
        }

        _dist[u] = INF;

        return false;
    }

    /* Constant used in the distance  */
    static constexpr int INF = 1e9;

    /* The adjacency list of a vertex of the left side to a vertex of the right side */
    std::vector<std::vector<int>> _adjU;

    /* The matched vertex of the right side */
    std::vector<int> _pairU;

    /* The matched vertex of the left side */
    std::vector<int> _pairV;

    /* The distance from a unmatched vertex  */
    std::vector<int> _dist;

    /* The number of nodes in the left side */
    int _m;

    /* The number of nodes in the right side */
    int _n;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int t;

	cin >> t;

	for(int i = 1; i <= t; ++i) {
		int n, m;

		cin >> n;

		vector<int> left(n);

		for(int& val : left) cin >> val;

		cin >> m;

		vector<int> right(m);

		for(int& val : right) cin >> val;

		HopcroftKarp hp(n, m);

		for(int k = 0; k < n; ++k) {
			for(int j = 0; j < m; ++j) {
				if(!left[k]) {
					if(!right[j])
						hp.add_edge(k + 1, j + 1);
				}
				else if(right[j] % left[k] == 0)
					hp.add_edge(k + 1, j + 1);
			}
		}

		cout << "Case " << i << ": " << hp.hopcroftKarp() << '\n';
	}

    return 0;
}
