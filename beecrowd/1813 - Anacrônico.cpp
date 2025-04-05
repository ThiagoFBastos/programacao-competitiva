#include <bits/stdc++.h>

using namespace std;

#define FOR(k, a, b) for(register int k = (a); k < (b); ++k)
#define REP(k, a, b) for(register int k = (a); k > (b); --k)
#define FORs(k, a, b, s) for(register int k = (a); k <= (b); k += s)

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

struct Edge {

	int to, cost, time;
};

bool operator<(Edge e1, Edge e2) {

	return e1.cost > e2.cost || (e1.cost == e2.cost && e1.time > e2.time);
}

#define MAXN 6001

int main() {
	
	int n, m, caso = 0;
	
	while(true) {
	
		int **e;
		
		scanf("%d%d", &n, &m);
		
		if(n == 0) break;
		
		e = new int*[n];
		
		FOR(k, 0, n) {
		
			e[k] = new int[MAXN];
			memset(e[k], -1, MAXN * sizeof(int));
		}
		
		vector<Edge> *N = new vector<Edge>[n];
		
		FOR(i, 0, m) {
		
			int u, v, custo, tempo;
			
			scanf("%d%d%d%d", &u, &v, &custo, &tempo);
			
			N[u - 1].push_back({v - 1, custo, tempo});
		}
		
		int queries;
		
		scanf("%d", &queries);
		
		printf("Instancia %d\n", ++caso);
		
		FOR(k, 0, queries) {
		
			int s, t, tempo, dist = -1, tmp;
			priority_queue<Edge> pq;
			
			scanf("%d%d%d", &s, &t, &tempo);
			
			--s, --t;
			
			pq.push({s, 0, 0});
			
			while(!pq.empty()) {
			
				int v, cst, tp;
				
				v = pq.top().to;
				cst = pq.top().cost;
				tp = pq.top().time;
				
				pq.pop();
				
				if(e[v][tp] < k) {
				
					e[v][tp] = k;
					
					if(v == t) {
					
						dist = cst;
						tmp = tp;
						break;
					}
					
					for(Edge E : N[v]) {
					
						int T = tp + E.time;
						int u = E.to;
						
						if(T <= tempo && e[u][T] < k)
							pq.push({u, E.cost + cst, T});
					}
				}
			}
			
			if(dist == -1) puts("Impossivel");
			else printf("Possivel - %d km, %d min\n", dist, tmp);
		}
		
		FOR(k, 0, n) 
			delete[] e[k];
		
		delete[] N;
		delete[] e;
		
		putchar_unlocked('\n');
	}
	
	return 0;
}