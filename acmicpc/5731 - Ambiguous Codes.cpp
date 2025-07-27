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

const int N = 101, M = 51;

int cost[N][M][N];

struct STATE {
	int s_i, pos_i;
	int s_j;
	int cost;
};

bool operator<(STATE a, STATE b) {
	return a.cost > b.cost;
}

void solve() {

	while(true) {
		int n;
		
		cin >> n;

		if(!n) break;

		vector<string> code(n);

		for(auto& s : code) cin >> s;

		for(int i = 0; i < n; ++i)
		for(int j = 0; j < (int)code[i].size(); ++j)
		for(int k = 0; k < n; ++k)
			cost[i][j][k] = -1;
			
		priority_queue<STATE> pq;

		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if(i == j) continue;
				pq.push({i, 0, j, 0});
			}
		}

		int ans = INF;

		while(!pq.empty()) {
			auto [s_i, pos_i, s_j, c] = pq.top(); pq.pop();

			if(cost[s_i][pos_i][s_j] != -1) continue;

			cost[s_i][pos_i][s_j] = c;			

			if(c > ans) break;

			auto& a = code[s_i];
			auto& b = code[s_j];

			int pos_j = 0;
			while(a[pos_i] && b[pos_j] && a[pos_i] == b[pos_j]) ++pos_i, ++pos_j, ++c;
			
			if(a[pos_i] && b[pos_j]) continue;
			else if(b[pos_j]) {
				for(int k = 0; k < n; ++k) {
					if(cost[s_j][pos_j][k] == -1)
						pq.push({s_j,pos_j,k,c});
				}
			} else if(a[pos_i]) {
				for(int k = 0; k < n; ++k) {
					if(cost[s_i][pos_i][k] == -1)
						pq.push({s_i,pos_i,k,c});
				}
			} else ans = min(ans, c);
		}

		cout << (ans == INF ? -1 : ans) << '\n';
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

