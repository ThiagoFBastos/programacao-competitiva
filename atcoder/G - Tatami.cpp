#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9;

struct dinic {
	int ned;
	vector<int> cap, nxt, first, to, work, dist;

	dinic(int n) {
		first.assign(n, -1);
		work.resize(n);
		dist.resize(n);
		ned = 0;
	}

	void add(int u, int v, int c) {
		to.emplace_back(v);
		cap.emplace_back(c);
		nxt.emplace_back(first[u]);
		first[u] = ned++;

		to.emplace_back(u);
		cap.emplace_back(0);
		nxt.emplace_back(first[v]);
		first[v] = ned++;
	}

	int dfs(int u, int f, int s, int t) {
		if(!f || u == t) return f;
		for(int& e = work[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if(dist[v] == dist[u] + 1 && cap[e] > 0) {
				int df = dfs(v, min(f, cap[e]), s, t);
				if(df > 0) {
					cap[e] -= df;
					cap[e ^ 1] += df;
					return df;
				}
			}
		}
		return 0;
	}

	bool bfs(int s, int t) {
		fill(dist.begin(), dist.end(), -1);
		dist[s] = 0;
		queue<int> q;
		q.push(s);
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int e = first[u]; e != -1; e = nxt[e]) {
				int v = to[e];
				if(dist[v] < 0 && cap[e] > 0) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
		return dist[t] >= 0;
	}

	int64_t maxflow(int s, int t) {
		int64_t res = 0;
		while(bfs(s, t)) {	
			copy(first.begin(), first.end(), work.begin());
			while(int f = dfs(s, INF, s, t))
				res += f;
		}
		return res;
	}
};

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int h, w;

    cin >> h >> w;

    vector<string> grid(h);

    pair<int, int> delta[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int cnt_2 {};

    for(auto& s : grid) cin >> s;

    int sz = 2 * h * w;
    dinic D(sz + 2);

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            D.add((i + h) * w + j, sz + 1, 1);
            if(grid[i][j] != '2') continue;  
            D.add(sz, i * w + j, 1);
            ++cnt_2;
            for(auto [dx, dy] : delta) {
                int x = i + dx, y = j + dy;
                if(x < 0 || y < 0 || x >= h || y >= w || grid[x][y] == '1') continue;
                D.add(i * w + j, (x + h) * w + y, 1);
            }
        }
    }
    
    cout << (D.maxflow(sz, sz + 1) == cnt_2 ? "Yes\n" : "No\n");

    return 0;
}
