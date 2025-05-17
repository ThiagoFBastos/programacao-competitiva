#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 3e3 + 5;
 
bool vis[N][N];
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	vector<string> grid(n);
	vector<pair<int, int>> S;
	string out;
 
	for(auto& s : grid) cin >> s;
 
	S.emplace_back(0, 0);
 
	while(!S.empty()) {
		char to = 'Z';
		vector<pair<int, int>> nextS;
 
		for(auto [i, j] : S) {
			if(i + 1 < n) to = min(to, grid[i + 1][j]);
			if(j + 1 < n) to = min(to, grid[i][j + 1]);
		}
 
		out += grid[S[0].first][S[0].second];
 
		for(auto [i, j] : S) {
			if(i + 1 < n && grid[i + 1][j] == to) {
				if(!vis[i + 1][j]) {
					nextS.emplace_back(i + 1, j);
					vis[i + 1][j] = true;
				}
			}
 
			if(j + 1 < n && grid[i][j + 1] == to) {
				if(!vis[i][j + 1]) {
					nextS.emplace_back(i, j + 1);
					vis[i][j + 1] = true;
				}
			}
		}
 
		swap(S, nextS);
	}
 
	cout << out << '\n';
 
	return 0;
}
