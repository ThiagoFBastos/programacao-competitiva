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

const int N = 1e3 + 10;

int tas, emp, sig[N], sal[N];
vector<int> daginv[N], work[N];
bool vis[N];
bitset<N> dt[N], mt[N];

vector<int> topo() {
	vector<int> A;
	memset(vis, 0, tas);
	auto dfs = [&](auto&& dfs, int u) {
		if(u < 0) return;
		vis[u] = true;
		for(int v : daginv[u]) if(!vis[v]) dfs(dfs, v);
		A.pb(u);
	};
	for(int i = 0; i < tas; ++i) if(!vis[i]) dfs(dfs, i);
	return A;
}

void solve() {

	while(true) {
		cin >> tas >> emp;

		if(tas + emp == 0) break;

		for(int i = 0; i < emp; ++i) {
			sal[i] = 0;
			mt[i].reset();
		}

		for(int i = 0; i < tas; ++i) {
			daginv[i].clear();
			dt[i].reset();
		}

		for(int i = 0; i < tas; ++i) {
			int nd, ne;

			cin >> sig[i] >> nd >> ne;

			while(nd--) {
				int t;
				cin >> t;
				daginv[i].pb(--t);
			}

			work[i].resize(ne);

			for(int& id : work[i]) {
				cin >> id;
				mt[--id][i] = 1;
			}
		}

		auto A = topo();

		for(int i = tas - 1; i >= 0; --i) {
			int v = A[i];
			dt[v][v] = 1;
			for(int u : daginv[v]) dt[u] |= dt[v];
		}

		for(int i = 0; i < tas; ++i) {
			int v = A[i];
			for(int u : daginv[v]) sig[v] += sig[u];
		}

		for(int i = 0; i < tas; ++i) {		
			dt[i][i] = 0;
			for(int id : work[i]) {
				if((dt[i] & mt[id]).none())
					sal[id] += sig[i];
			}
		}

		cout << "*****\n";
		for(int i = 0; i < emp; ++i) cout << i + 1 << ' ' << sal[i] << '\n';
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
