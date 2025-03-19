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
#define all_r(x) x.rbegin(), x.rend()
#define pb push_back
#define FOR(i, n) for(int i = 0; i < (n); ++i)
#define range(i, a, b) for(int i = a; i < (b); ++i)
#define f first
#define s second
const int MAXN = 1e5, MOD = 1e9 + 7;
struct porta {
	int e, d, f;
} p[MAXN];
int n; 
ll vv[MAXN], ff[MAXN], vf[MAXN], fv[MAXN];
void dfs(int v) {
	auto [e, d, f] = p[v];
	ll e_vv, e_ff, e_fv, e_vf, d_vv, d_ff, d_fv, d_vf;
	if(e == -1) {
		e_vv = e_ff = 1;
		e_fv = e_vf = 0;
	}
	else {
		dfs(e);		
		e_vv = vv[e];
		e_ff = ff[e];
		e_fv = fv[e];
		e_vf = vf[e];
	}
	if(d == -1) {
		d_vv = d_ff = 1;
		d_vf = d_fv = 0;
	}
	else {
		dfs(d);
		d_vv = vv[d];
		d_ff = ff[d];
		d_vf = vf[d];
		d_fv = fv[d];
	}
	if(f == -1) {
		vv[v] = (
				e_vv * d_ff % MOD +
			 
				e_fv * d_vf % MOD +
				e_fv * d_ff % MOD +

				e_vf * d_fv % MOD +
				e_vf * d_ff % MOD +

				e_ff * d_vv % MOD +
				e_ff * d_ff % MOD +
				e_ff * d_vf % MOD +
				e_ff * d_fv % MOD 
				) % MOD;

		ff[v] = e_vv * d_vv % MOD;

		vf[v] = (
				e_vv * d_fv +
				e_fv * d_vv +
				e_fv * d_fv
				) % MOD;

		fv[v] = (
				e_vv * d_vf +
				e_vf * d_vf +
				e_vf * d_vv 
				) % MOD;
	}
	else if(f) {
		ff[v] = fv[v] = 0;
		vv[v] = (
				e_vv * d_ff % MOD +
				e_vv * d_vf % MOD +
				
				e_ff * d_vv % MOD +
				e_ff * d_vf % MOD +
				e_ff * d_fv % MOD +
				e_ff * d_ff % MOD +

				e_fv * d_ff % MOD +
				e_fv * d_vf % MOD +

				e_vf * d_ff % MOD +
				e_vf * d_vf % MOD +
				e_vf * d_fv % MOD +
				e_vf * d_vv % MOD
				) % MOD;	
		vf[v] = (
				e_vv * d_vv % MOD +
				e_vv * d_fv % MOD +
				e_fv * d_vv % MOD +
				e_fv * d_fv % MOD
				) % MOD;
	}
	else {
		vv[v] = vf[v] = 0;
		ff[v] = (
				e_vv * d_vv % MOD +
				e_vv * d_fv % MOD + 
					
				e_fv * d_fv % MOD +
				e_fv * d_vv % MOD				
				) % MOD;
		fv[v] = (
				e_vv * d_ff % MOD +
				e_vv * d_vf % MOD +

				e_fv * d_ff % MOD +
				e_fv * d_vf % MOD +

				e_ff * d_ff % MOD +
				e_ff * d_vv % MOD +
				e_ff * d_vf % MOD +
				e_ff * d_fv % MOD +
		
				e_vf * d_vf % MOD +
				e_vf * d_vv % MOD +	
				e_vf * d_ff % MOD +
				e_vf * d_fv % MOD				
				) % MOD;
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	FOR(i, n) {
		cin >> p[i].e >> p[i].d >> p[i].f;
		--p[i].e, --p[i].d;
	}
	dfs(0);
	cout << (vf[0] + fv[0]) % MOD << '\n';
	return 0;
}