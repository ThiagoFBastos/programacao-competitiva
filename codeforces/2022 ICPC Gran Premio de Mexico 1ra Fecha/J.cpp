#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 3e5;
const int MAXM = 3e5;

int ned, first[MAXN], work[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init() {
    memset(first, -1, sizeof first);
}

void add(int u, int v, int f) {
    to[ned] = v;
    cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    to[ned] = u;
    cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
    if(u == t) return f;
    int v, df;
    for(int& e = work[u]; e != -1; e = nxt[e]) {
        v = to[e];
        if(dist[v] == dist[u] + 1 && cap[e] > 0) {
            df = dfs(v, min(f, cap[e]), s, t);
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
    int u, v;
    memset(dist, -1, sizeof dist);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int e = first[u]; e != -1; e = nxt[e]) {
            v = to[e];
            if(dist[v] < 0 && cap[e] > 0) {
                dist[v] = 1 + dist[u];
                q.push(v);
            }
        }
    }
    return dist[t] >= 0;
}

int dinic(int s, int t) {
    int res = 0;
    while(bfs(s, t)) {
        memcpy(work, first, sizeof work);
        while(int f = dfs(s, INF, s, t)) res += f;
    }
    return res;
}

void solve() {
   int n, m;
   
   cin >> n >> m;
   
   init();
   
   for(int i = 0; i < n; ++i) {
       int k;
       cin >> k;
       add(n + m, i, 1);
       while(k--) {
           int j;
           cin >> j;
           add(i, n + j - 1, 1);
       }
   }
   
   for(int j = 0; j < m; ++j) add(n + j, n + m + 1, 1);
  
   cout << m - dinic(n + m, n + m + 1) << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  //cin >> t;
	while(t--) solve();
	return 0;
}


