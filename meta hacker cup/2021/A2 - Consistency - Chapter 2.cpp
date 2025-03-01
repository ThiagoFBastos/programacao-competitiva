#include "bits/stdc++.h"

using namespace std;

int g[26][26], dist[26][26];

void solve() {
	string s;
	int m, swaps = INT_MAX;
	cin >> s >> m;
	
	for(int i = 0; i < 26; ++i)
		for(int j = 0; j < 26; ++j)
			g[i][j] = dist[i][j] = -1;
		
	while(m--) {
		string s;
		cin >> s;
		g[s[0] - 'A'][s[1] - 'A'] = 1;
	}
	
	for(int i = 0; i < 26; ++i) {
		queue<int> q;
		dist[i][i] = 0;
		q.push(i);
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			for(int u = 0; u < 26; ++u) {
				if(dist[i][u] != -1 || g[v][u] == -1) continue;
				dist[i][u] = 1 + dist[i][v];
				q.push(u);
			}
		}
	}
	
	for(int i = 0; i < 26; ++i) {
		int cnt = 0;
		for(char ch : s) {
			if(dist[ch - 'A'][i] == -1) {
				cnt = INT_MAX;
				break;
			}
			cnt += dist[ch - 'A'][i];
		}
		swaps = min(swaps, cnt);
	}
	
	if(swaps == INT_MAX) cout << "-1\n";
	else cout << swaps << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int k = 1; k <= t; ++k) {
		cout << "Case #" << k << ": ";
		solve();
	}
 	return 0;
}
