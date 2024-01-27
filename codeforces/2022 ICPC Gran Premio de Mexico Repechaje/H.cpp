#include "bits/stdc++.h"
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>


using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, 
tree_order_statistics_node_update>;
 
#define INF   1000000000
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
using i128 = __int128;

int ned;
vector<int> cap, to, nxt, dist, first, work;
int n, m;

void init(int n) {
    first.assign(n, -1);
    work.resize(n);
    dist.resize(n);
}

void add(int u, int v, int c) {
  to.pb(v);
  cap.pb(c);
  nxt.pb(first[u]);
  first[u] = ned++;
  to.pb(u);
  cap.pb(0);
  nxt.pb(first[v]);
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
  fill(all(dist), -1);
  dist[s] = 0;
  queue<int> q;
  q.push(s);
  while(!q.empty()) {
    int u = q.front(); q.pop();
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

i64 maxflow(int s, int t) {
  i64 res = 0;
  while(bfs(s, t)) {
    copy(all(first), work.begin());
    while(int f = dfs(s, INF, s, t))
      res += f;
  }
  return res;
}

void solve() {
    
  cin >> n >> m;
  
  vector<int> in(n, 0), out(n, 0), deg(n, 0);
  
  init(n + m + 2);
  
  for(int i = 0; i < m; ++i) {
   int a, b, c;
   cin >> a >> b >> c;
   --a, --b;
   ++deg[a], ++deg[b];
    if(c) ++in[b], ++out[a];
    else {
      add(n + i, a, 1);
      add(n + i, b, 1);
    }
    add(n + m, n + i, 1);
  }
  
  int need = 0;
  
  for(int i = 0; i < n; ++i) {
    if(deg[i] % 2 || max(in[i], out[i]) * 2 > deg[i]) {
      cout << "NO\n";
      return;
    }
    need += deg[i] / 2 - in[i];
    add(i, n + m + 1, deg[i] / 2 - in[i]);
  }
  
  i64 f = maxflow(n + m, n + m + 1);
  
  if(f != need) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
  	//cin >> t;
	while(t--) solve();
	return 0;
}
