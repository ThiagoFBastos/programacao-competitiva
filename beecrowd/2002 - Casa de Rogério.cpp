#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,mmx,sse2")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

static ll C(ll X);

ll C(ll X) {
	int k = 0, bit[64];
	ll ans = 0, Z = 1;
	memset(bit, 0, sizeof bit);
	while(X > 0) {
		int d = X & 1;
		bit[k] ^= d & Z & 1;
		if(d && k == 1) bit[0] ^= 1;
		Z += (ll)d << k;
		X >>= 1;
		++k;
	}
	for(int i = 0; i < k; ++i) ans |= (ll)bit[i] << i;
	return ans;
}

struct trajeto {
	int dx, dy;
	ll custo;
};

bool operator<(trajeto t1, trajeto t2) {
	return t1.custo > t2.custo;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int N, M, dxy[4][2] = {
		{-1, 0},
		{1, 0},
		{0, -1},
		{0, 1}
	};
	ll g[102][102], g1[102][102], g2[102][102], e[102][102][4], cp[102][102];
	bool p[102][102];
	while(cin >> N >> M) {
		for(int k = 0; k <= N; ++k) {
			for(int i = 0; i <= M; ++i) {
				cp[k][i] = LLONG_MAX;
				p[k][i] = false;
				for(int j = 0; j < 4; ++j)
					e[k][i][j] = -1;	
			}
		}
		for(int k = 0; k <= M; ++k) {
			p[N + 1][k] = p[0][k] = true;
			g[0][k] = g[N + 1][k] = cp[N + 1][k] = cp[0][k] = 0;
		}
		for(int k = 0; k <= N; ++k) {
			p[k][0] = p[k][M + 1] = true;
			g[k][0] = g[k][M + 1] = cp[k][0] = cp[k][M + 1] = 0;
		}
		for(int k = 1; k <= N; ++k) {
			for(int i = 1; i <= M; ++i) {
				cin >> g[k][i];
				g1[k][i] = C(g[k][i]);
				g2[k][i] = C(g[k][i] - 1);
			}
		}
		for(int k = 1; k <= N; ++k) {
			for(int i = 1; i <= M; ++i) {
				for(int j = 0; j < 4; ++j) {
					int x = k + dxy[j][0], y = i + dxy[j][1];
					e[k][i][j] = g[k][i] >= g[x][y] ? g1[k][i] ^ g2[x][y] : g1[x][y] ^ g2[k][i];
				}
			}
		}
		priority_queue<trajeto> pq;
		cp[1][1] = 0;
		pq.push({1, 1, 0});
		while(!pq.empty()) {
			int dx, dy;
			ll cst;
			dx = pq.top().dx, dy = pq.top().dy, cst = pq.top().custo;
			pq.pop();
			if(p[dx][dy]) continue;
			else if(dx == N && dy == M) break;
			p[dx][dy] = true;
			for(int j = 0; j < 4; ++j) {
				int x = dx + dxy[j][0], y = dy + dxy[j][1];
				if(cp[x][y] > cst + e[dx][dy][j]) {
					cp[x][y] = cst + e[dx][dy][j];
					pq.push({x, y, cp[x][y]});
				}
			}
		}
		cout << cp[N][M] << '\n';
	}
	return 0;
}