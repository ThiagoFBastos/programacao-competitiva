#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	int n, m, ***p, x0, y0, x1, y1;
	char **g;
	queue<ii> Q;
	scanf("%d%d", &n, &m);
	g = new char*[n];
	p = new int**[n];
	for(int i = 0; i < n; ++i) {
		g[i] = new char[m + 1];
		p[i] = new int*[m];
		scanf("%s", g[i]);
		for(int k = 0; k < m; ++k) {
			if(g[i][k] == 'A') x1 = i, y1 = k;
			else if(g[i][k] == 'B') x0 = i, y0 = k;
			p[i][k] = new int[2];
			p[i][k][0] = -1;
		}
	}
	p[x0][y0][0] = x0;
	Q.push({x0, y0});
	while(!Q.empty()) {
		auto [x, y] = Q.front();
		Q.pop();
		if(g[x][y] == '#') continue;
		else if(x == x1 && y == y1) break;
		if(x < n - 1 && p[x + 1][y][0] == -1) {
			p[x + 1][y][0] = x;
			p[x + 1][y][1] = y;
			Q.push({x + 1, y});
		}
		if(x && p[x - 1][y][0] == -1) {
			p[x - 1][y][0] = x;
			p[x - 1][y][1] = y;
			Q.push({x - 1, y});
		}
		if(y < m - 1 && p[x][y + 1][0] == -1) {
			p[x][y + 1][0] = x;
			p[x][y + 1][1] = y;
			Q.push({x, y + 1});
		}
		if(y && p[x][y - 1][0] == -1) {
			p[x][y - 1][0] = x;
			p[x][y - 1][1] = y;
			Q.push({x, y - 1});
		}
	}
	if(p[x1][y1][0] == -1)
		puts("NO");
	else {
		string path;
		while(!(x1 == x0 && y1 == y0)) {
			int x = x1, y = y1;
			x1 = p[x][y][0];
			y1 = p[x][y][1];
			if(x1 == x - 1) path.push_back('U');
			else if(x1 == x + 1) path.push_back('D');
			else if(y1 == y - 1) path.push_back('L');
			else path.push_back('R');
		}
		printf("YES\n%d\n%s\n", path.size(), path.c_str());
	}	
    return 0;
}
