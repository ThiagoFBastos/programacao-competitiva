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
using i128 = __int128;

const int N = 1e2+10;
int color[N][N], h, w, n;

ii delta[] = {
	{1, 0},
	{0,1},
	{0,-1},
	{-1,0}
};

int valid(int x, int y) {
	return x >= 0 && x < h && y >= 0 && y < w && !color[x][y];
}

int deg(int i, int j) {
	int n = 0;
	for(auto [dx, dy] : delta) n += valid(i + dx, j + dy);
	return n;
}

void solve() {

	cin >> h >> w >> n;

	set<pair<int, ii>> st;

	for(int x = 0; x < h; ++x)
		for(int y = 0; y < w; ++y)
			st.emplace(deg(x, y), ii(x, y));

	for(int k = 1; k <= n; ++k) {
		int a;	
		set<pair<int, ii>> aux;

		cin >> a;
		
		aux.insert(*st.begin());
		st.erase(st.begin());

		for(int j = 0; j < a; ++j) {
			auto [_, p] = *aux.begin();
			auto [x, y] = p;
			color[x][y] = k;
			aux.erase(aux.begin());
			for(auto [dx, dy] : delta) {
				int i = x + dx, j = y + dy;
				if(!valid(i, j)) continue;
				int d = deg(i, j);		
				st.erase(make_pair(d + 1, ii(i, j)));
				aux.erase(make_pair(d + 1, ii(i, j)));
				aux.insert(make_pair(d, ii(i, j)));
			}
		}

		while(!aux.empty()) {
			st.insert(*aux.begin());
			aux.erase(aux.begin());
		}
	}

	for(int x = 0; x < h; ++x) {
		for(int y = 0; y < w; ++y)
			cout << color[x][y] << ' ';
		cout << '\n';
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
	return 0;
}

