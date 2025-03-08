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

const int maxn = 2e5 + 1, mod = 1e9 + 7, maxnodes = (1 << 19) + 20 * 200000;
int N, K, Q, t[(int)1e4 + 1], tr[(int)1e4 + 1];

int st1[maxnodes], st2[maxnodes], L[maxnodes], R[maxnodes], root[maxn], no;

static void build(int, int);
static void upd(int, int, int, int, int);
static ii query(int, int, int, int, int);
static int expmod(int, int);

void build(int lo, int hi) {
	if(lo == hi) {
		st1[no] = 0;
		st2[no] = 1;
		++no;
	} else {
		int mid = (lo + hi) >> 1, node = no++;
		L[node] = no;
		build(lo, mid);
		R[node] = no;
		build(mid + 1, hi);
		st1[node] = 0;
		st2[node] = 1;
	}
}

void upd(int k, int lo, int hi, int node) {
	if(lo == hi) {
		st1[no] = st1[node] + 1;
		st2[no] = 1ll * st2[node] * tr[k] % mod;
		++no;
	} else {
		int mid = (lo + hi) >> 1, v = no++;
		if(k <= mid) {
			L[v] = no;
			R[v] = R[node];
			upd(k, lo, mid, L[node]);
		} else {
			L[v] = L[node];
			R[v] = no;
			upd(k, mid + 1, hi, R[node]);
		}
		st1[v] = st1[L[v]] + st1[R[v]];
		st2[v] = 1ll * st2[L[v]] * st2[R[v]] % mod;
	}
}

ii query(int k, int lo, int hi, int noL, int noR) {
	if(lo == hi) return {1, expmod(tr[lo], k)};
	int mid = (lo + hi) >> 1, LL = L[noL], LR = R[noL], RL = L[noR], RR = R[noR];
	if(st1[RL] - st1[LL] >= k) return query(k, lo, mid, LL, RL);
	ii esq {st2[LL], st2[RL]};
	ii dir = query(k - st1[RL] + st1[LL], mid + 1, hi, LR, RR);
	return {1ll * esq.first * dir.first % mod, 1ll * esq.second * dir.second % mod};	
}

int expmod(int a, int p) {
	int res = 1;
	while(p > 0) {
		if(p & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		p >>= 1;
	}
	return res;
}

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	vi m_i, a, p;
	int cnt = 0;

	cin >> N >> K >> Q;
	
	a.resize(N);
	m_i.resize(N);
	p.resize(N + 1);

	p[0] = 0;

	for(int i = 0; i < N; ++i) {
		cin >> a[i];
		m_i[i] = a[i];
		p[i + 1] = p[i];
		if(a[i] == 0) ++p[i + 1];
	}

	sort(m_i.rbegin(), m_i.rend());
	
	for(int k = 0, i; k < N; k = i) {
		for(i = k; i < N && m_i[k] == m_i[i]; ++i);
		t[m_i[k]] = cnt;
		tr[cnt] = m_i[k];
		++cnt;
	}

	build(0, cnt - 1);
	root[0] = 0;

	for(int i = 1; i <= N; ++i) {
		root[i] = no;
		upd(t[a[i - 1]], 0, cnt - 1, root[i - 1]);
	}

	while(Q--) {
		int ini, fim, cho;
		cin >> ini >> fim;
		cho = min(K, fim - ini + 1 - p[fim] + p[ini - 1]);
		if(cho <= 0)
			cout << 0 << '\n';
		else {
			ii res = query(cho, 0, cnt - 1, root[ini - 1], root[fim]);
			cout << 1ll * res.second * expmod(res.first, mod - 2) % mod << '\n';
		}
	}

	return 0;
}