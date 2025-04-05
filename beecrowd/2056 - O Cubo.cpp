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
#define mp make_pair

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

typedef unsigned long long ull;
typedef long long ll;

#define MAXN 20

struct DATA {

	int x1, y1, x2, y2, mov, push;
};

bool operator<(DATA d1, DATA d2) {

	return d1.push > d2.push || (d1.push == d2.push && d1.mov > d2.mov);
}

int main() {

	char grid[MAXN][MAXN + 1];
	bool e[400][400];
	int r, c, caso = 0;
	
	while(true) {
	
		scanf("%d%d", &r, &c);
		
		if(!(r || c)) break;
		
		priority_queue<DATA> pq;
		
		int N = r * c;
		
		FOR(x, 0, N)
			memset(e[x], false, N * sizeof(bool));
						
		FOR(k, 0, r)
			scanf("%s", grid[k]);
			
		int x1, y1, x2, y2, x3, y3;
		
		FOR(k, 0, r) {
		
			FOR(i, 0, c) {
			
				if(grid[k][i] == 'B') {x2 = k, y2 = i; grid[k][i] = '.';}
				else if(grid[k][i] == 'T') {x3 = k, y3 = i; grid[k][i] = '.';}
				else if(grid[k][i] == 'S') {x1 = k, y1 = i;	grid[k][i] = '.';}		
			}
		}
		
		pq.push({x1, y1, x2, y2, 0, 0});
		
		int movs = -1, pushes;
		
		while(!pq.empty()) {
		
			auto [x1, y1, x2, y2, mv, ps] = pq.top();
			
			pq.pop();
				
			int end1 = x1 * c + y1, end2 = x2 * c + y2;
			
			if(!e[end1][end2]) {
			
				e[end1][end2] = true;
				
				if(x2 == x3 && y2 == y3) {
				
					movs = mv;
					pushes = ps;
					
					break;
				}
				
				if(x1 && end1 - c != end2 && !e[end1 - c][end2] && grid[x1 - 1][y1] == '.')
					pq.push({x1 - 1, y1, x2, y2, mv + 1, ps});
						 
				else if(x1 > x2 && x2 && end1 - c == end2 && grid[x2 - 1][y2] == '.' && !e[end1 - c][end2 - c])
					pq.push({x1 - 1, y1, x2 - 1, y2, mv + 1, ps + 1});
				
				if(x1 < r - 1 && end1 + c != end2 && !e[end1 + c][end2] && grid[x1 + 1][y1] == '.')
					pq.push({x1 + 1, y1, x2, y2, mv + 1, ps});
						 
				else if(x1 < x2 && x2 < r - 1 && end1 + c == end2 && grid[x2 + 1][y2] == '.' && !e[end1 + c][end2 + c])
					pq.push({x1 + 1, y1, x2 + 1, y2, mv + 1, ps + 1});
				
				if(y1 && !e[end1 - 1][end2] && grid[x1][y1 - 1] == '.' && end1 - 1 != end2)
					pq.push({x1, y1 - 1, x2, y2, mv + 1, ps});
						 
				else if(y1 > y2 && y2 && grid[x2][y2 - 1] == '.' && !e[end1 - 1][end2 - 1] && end1 - 1 == end2)
					pq.push({x1, y1 - 1, x2, y2 - 1, mv + 1, ps + 1});
				
				if(y1 < c - 1 && end1 + 1 != end2 && !e[end1 + 1][end2] && grid[x1][y1 + 1] == '.')
					pq.push({x1, y1 + 1, x2, y2, mv + 1, ps});
						 
				else if(y1 < y2 && y2 < c - 1 && end1 + 1 == end2 && grid[x2][y2 + 1] == '.' && !e[end1 + 1][end2 + 1])
					pq.push({x1, y1 + 1, x2, y2 + 1, mv + 1, ps + 1});
			}
		}
		
		if(caso) putchar('\n');
		
		printf("Instancia %d\n", ++caso);
		
		if(movs == -1) puts("Impossivel");
		else printf("%d %d\n", movs, pushes);
		
	}

	return 0;
}