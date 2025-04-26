#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse,sse2")
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

#define all(x) x.begin(), x.end()
#define pb push_back
#define FOR(i, n) for(int i = 0; i < (n); ++i)
#define f first
#define s second

const int MAXN = 100;
int c[MAXN];

int matching(int m, int n1, int n2, vvii& S, vvii& C) {
	bool M[10000], sl[MAXN];
	int cl[MAXN], ps[MAXN][2], pc[MAXN][2];
	memset(M, 0, m);
	memset(cl, 0, n2 * sizeof(int));
	FOR(v, n1) sl[v] = true;
	while(true) {
		queue<ii> Q;
		FOR(v, n1) {
			ps[v][0] = -1;
			if(sl[v]) {
				ps[v][0] = v;
				ps[v][1] = -1;
				Q.push({v, 0});
			}
		}
		FOR(v, n2) pc[v][0] = -1;
		int u = -1;
		while(!Q.empty()) {
			auto [v, t] = Q.front();
			Q.pop();
			if(t) {
				if(cl[v] < c[v]) {
					u = v;
					break;
				}
				for(auto [u, e_pos] : C[v]) {
					if(ps[u][0] == -1 && M[e_pos]) {
						ps[u][0] = v;
						ps[u][1] = e_pos;
						Q.push({u, 0});
					}
				}
			}
			else {
				for(auto [u, e_pos] : S[v]) {
					if(pc[u][0] == -1 && !M[e_pos]) {
						pc[u][0] = v;
						pc[u][1] = e_pos;			
						Q.push({u, 1});
					}
				}
			}
		}
		if(u == -1) break;
		++cl[u];
		for(int t = 1; ; t ^= 1) {
			int v;
			if(t) {
				v = pc[u][0];	
				M[pc[u][1]] = true;
			}
			else {
				v = ps[u][0];
				sl[u] = false;
				if(ps[u][1] == -1) break;
				M[ps[u][1]] = false;
			}
			u = v;
		}
	}
	int emp = 0;
	FOR(e, m) if(M[e]) ++emp;
	return emp;
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m, k, caso = 0;
	while(cin >> n >> m >> k) {
		vvii S(m), C(n);
		FOR(i, n) cin >> c[i];
		FOR(i, k) {
			int a, b;
			cin >> a >> b;
			--a, --b;
			S[b].pb({a, i});
			C[a].pb({b, i});
		}
		cout << "Instancia " << ++caso << '\n' << matching(k, m, n, S, C) << "\n\n";
	}
	return 0;
}