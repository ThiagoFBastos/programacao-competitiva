#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2")

#define f first
#define s second

using namespace std;

typedef long long ll;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

class unionfind {

	vi pa, rank;

	public:

	unionfind() {}

	unionfind(int n) {

		pa.resize(n);
		rank.resize(n);

		for(int k = 0; k < n; ++k)
			pa[k] = k, rank[k] = 0;
	}

	int findSet(int v) {
		return v == pa[v] ? v : pa[v] = findSet(pa[v]);
	}

	void link(int v1, int v2) {
		if(rank[v1] < rank[v2]) pa[v1] = v2;
		else {
			pa[v2] = v1;
			if(rank[v1] == rank[v2]) ++rank[v1];
		}
	}
};

vector<vi> G;
vi cc;

int w = 0;

void dfs(int v) {

	cc[v] = w;

	for(int w : G[v]) {

		if(cc[w] == -1)
			dfs(w);
	}
}

int main() {
  
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int N, M;
	
	cin >> N >> M;

	vii edge(M);
	vi count(M, 0);
	
	G.resize(N);
	cc.assign(N, -1);

	for(ii& e: edge) {

		cin >> e.f >> e.s;
		--e.f, --e.s;
	}

 	int Q;

	cin >> Q;

	vi queries(Q);

	for(int& x : queries) {

		cin >> x;
		++count[--x];
		
	}

	for(int k = 0; k < M; ++k) {

		if(!count[k]) {
			
			G[edge[k].f].push_back(edge[k].s);
			G[edge[k].s].push_back(edge[k].f);
		}
	}

	for(int k = 0; k < N; ++k) {

		if(cc[k] == -1) {

			dfs(k);
			++w;
		}
	}

	unionfind S(w);
	vi ans(Q);

	ans[Q - 1] = w;

	for(int k = Q - 1; k > 0; --k) {

		int u = edge[queries[k]].f, v = edge[queries[k]].s;

		int up = S.findSet(cc[u]), vp = S.findSet(cc[v]);

		--count[queries[k]];

		if(up == vp || count[queries[k]])
			ans[k - 1] = ans[k];

		else {

			ans[k - 1] = ans[k] - 1;
			S.link(vp, up);
		}
	}

	for(int k = 0; k < Q - 1; ++k) cout << ans[k] << ' ';

	cout << ans.back() << '\n';

    return 0;
}