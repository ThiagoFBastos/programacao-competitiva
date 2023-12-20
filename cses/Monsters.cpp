#include <bits/stdc++.h>
#pragma optimize ("O3")
#pragma target ("sse,sse2")
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
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, **tm, **t, x, y;
	char **G;
	ii **p;
	cin >> n >> m;
	G = new char*[n];
	tm = new int*[n];
	t = new int*[n];
	p = new ii*[n];
	for(int i = 0; i < n; ++i) {
		G[i] = new char[m + 1];
		p[i] = new ii[m];
	    tm[i] = new int[m];
		t[i] = new int[m];
		cin >> G[i];
		for(int k = 0; k < m; ++k) {
			tm[i][k] = INT_MAX;
			t[i][k] = -1;
			if(G[i][k] == 'A') x = i, y = k;
		}
	}
	queue<ii> Q;
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(G[i][j] == '#') tm[i][j] = t[i][j] = 0;
			else if(G[i][j] == 'M') {
				tm[i][j] = 0;
				Q.push({i, j});
			}
		}
	}
	while(!Q.empty()) {
		auto [i, j] = Q.front();
		Q.pop();
		if(i < n - 1 && tm[i + 1][j] == INT_MAX) {
			tm[i + 1][j] = 1 + tm[i][j];
			Q.push({i + 1, j});
		}
		if(i && tm[i - 1][j] == INT_MAX) {
			tm[i - 1][j] = 1 + tm[i][j];
			Q.push({i - 1, j});
		}
		if(j < m - 1 && tm[i][j + 1] == INT_MAX) {
			tm[i][j + 1] = 1 + tm[i][j];
			Q.push({i, j + 1});
		}
		if(j && tm[i][j - 1] == INT_MAX) {
			tm[i][j - 1] = 1 + tm[i][j];
			Q.push({i, j - 1});
		}
	}
	Q.push({x, y});
	t[x][y] = 0;
	int x1 = -1, y1;
	while(!Q.empty()) {
		auto [i, j] = Q.front();
		if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {x1 = i, y1 = j; break;}
		Q.pop();
		if(i < n - 1 && t[i + 1][j] == -1) {
			t[i + 1][j] = 1 + t[i][j];
			p[i + 1][j] = make_pair(i, j);
			if(t[i + 1][j] < tm[i + 1][j])
				Q.push({i + 1, j});
		}
		if(i && t[i - 1][j] == -1) {
			t[i - 1][j] = 1 + t[i][j];
			p[i - 1][j] = make_pair(i, j);
			if(t[i - 1][j] < tm[i - 1][j])
				Q.push({i - 1, j});
		}
		if(j < m - 1 && t[i][j + 1] == -1) {
			t[i][j + 1] = 1 + t[i][j];
			p[i][j + 1] = make_pair(i, j);
			if(t[i][j + 1] < tm[i][j + 1])
				Q.push({i, j + 1});
		}
		if(j && t[i][j - 1] == -1) {
			t[i][j - 1] = 1 + t[i][j];
			p[i][j - 1] = make_pair(i, j);
			if(t[i][j - 1] < tm[i][j - 1])
				Q.push({i, j - 1});
		}
	}
	if(x1 == -1) cout << "NO\n";
	else {
		stack<char> path;
		cout << "YES\n";
		cout << t[x1][y1] << '\n';
		while(!(x1 == x && y1 == y)) {
			int x0 = x1, y0 = y1;
			x1 = p[x0][y0].f;
			y1 = p[x0][y0].s;
			if(x0 < x1) path.push('U');
			else if(x0 > x1) path.push('D');
			else if(y0 > y1) path.push('R');
			else path.push('L');
		}
		while(!path.empty()) {
			cout << path.top();
			path.pop();
		}
		cout << '\n';
	}
    return 0;
}
