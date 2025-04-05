#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(int k = (a); k < (b); ++k)
#define REP(k, a, b) for(int k = (a); k > (b); --k)

#define all(x) x.begin(), x.end()
#define up(x, y) upper_bound(all(x), y)
#define lower(x, y) lower_bound(all(x), y)
#define INF 0x3ffffff
#define fi first
#define sc second

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

typedef unsigned long long ull;
typedef long long ll;

struct Node {

	int sede, medalhas, criacao, id;
};

#define MAXN 100000

int main() {

	int n, m, q, s;
	Node sedes[MAXN];
	
	while(scanf("%d%d%d%d", &n, &s, &q, &m) != EOF) {
	
		vi *G = new vi[n];
		int *sede = new int[n];
		int *dist = new int[n];
		queue<int> Q;
		
		memset(dist, -1, n * sizeof(int));
		
		FOR(k, 0, s) {
		
			Node node;
			
			scanf("%d%d%d", &node.sede, &node.medalhas, &node.criacao);
			
			node.id = k + 1;
			
			int v = --node.sede;
			
			if(dist[v] == -1) {
			
				sede[v] = v;
				
				sedes[v] = node;
				
				dist[v] = 0;
				
				Q.push(v);
			}
			
			else if(node.medalhas > sedes[v].medalhas || (node.medalhas == sedes[v].medalhas && node.criacao > sedes[v].criacao))
				sedes[v] = node;
		}
		
		FOR(i, 0, m) {
		
			int u, v;
			
			scanf("%d%d", &u, &v);
			
			--u, --v;
			
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		while(!Q.empty()) {
		
			int w = Q.front();
			
			Q.pop();
			
			int u = sede[w];
			
			for(int v : G[w]) {
					
				if(dist[v] == -1) {
				
					sede[v] = u;
					dist[v] = 1 + dist[w];
					Q.push(v);
				}
				
				else if(dist[v] == 1 + dist[w] && (sedes[sede[v]].medalhas < sedes[u].medalhas || (sedes[sede[v]].medalhas == sedes[u].medalhas && sedes[sede[v]].criacao < sedes[u].criacao)))
					sede[v] = u;
			}
		}
		
		while(q--) {
		
			int x;
			
			scanf("%d", &x);
			
			if(dist[--x] == -1)
				puts("Noic");
				
			else
				printf("%d\n", sedes[sede[x]].id);
		}
		
		delete[] G;
		delete[] sede;
		delete[] dist;
	}
	
	return 0;
}