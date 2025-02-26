#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

using T = tuple<int, int, int, int>;

const int N = 50, inf = 1e9;

int custo[512][N][N];
bool visto[512][N][N];

void solve() {
	int n, m;
	
	cin >> n >> m;
	
	vector<string> g(n);
	
	for(string& s : g) {
		cin >> s;
		for(char& ch : s) {
			if(ch == 'p') ch = 'e';
			else if(ch == 't') ch = 'f';
			else if(ch == 'm') ch = 'g';
			else if(ch == 'e') ch = 'h';
			else if(ch == 'r') ch = 'i';
			else if(ch == 'T') ch = '@';
		}
	}
		
	for(int a = 0; a < 512; ++a)
	for(int b = 0; b < n; ++b)
	for(int c = 0; c < m; ++c)
		custo[a][b][c] = inf;
		
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(g[i][j] != '@') continue;
			
			priority_queue<T> pq;
			
			custo[0][i][j] = 0;
			pq.emplace(0, 0, i, j);
			
			while(!pq.empty()) {
				auto [c, mask, x, y] = pq.top();
				pq.pop();
				
				if(visto[mask][x][y]) continue;
				else if((mask >> 4) == 31) {
					cout << -c << '\n';
					return;
				}
					
				c *= -1;
				visto[mask][x][y] = true;
				
				for(int dx = -1; dx <= 1; ++dx) {
					for(int dy = -1; dy <= 1; ++dy) {
						if(abs(dx) + abs(dy) != 1) continue;
						
						int X = x + dx, Y = y + dy, new_mask = mask;
						
						if(X < 0 || Y < 0 || X == n || Y == m) continue;
						
						if(islower(g[X][Y])) new_mask |= 1 << (g[X][Y] - 'a');
						else if(g[X][Y] == '#' || isupper(g[X][Y]) && !(mask & 1 << (g[X][Y] - 'A'))) continue;
						
						if(custo[new_mask][X][Y] > c + 1) {
							custo[new_mask][X][Y] = c + 1;
							pq.emplace(-c - 1, new_mask, X, Y);
						}
					}
				}
			}
			
			cout << "Gamora\n";
			
			return;
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}