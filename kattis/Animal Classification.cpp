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

const int maxn = 2e5 + 1;
int n, ans, A, B;
string a, b;
int TA[maxn][2], TB[maxn][2], sp[18][maxn];
vi RA, RB, sz, LCA, lv, sub;

int lca(int, int);
int init(int [][2], vi&, string&);
void dfsB(int, int);
void dfsA(int);

int init(int T[][2], vi& R, string& s) {
    int v = 0;
    stack<int> V;
	int cnt = n + count(s.begin(), s.end(), '('); 
    R.resize(n);
	for(int i = 0; i < cnt; ++i)
		T[i][0] = T[i][1] = -1;
    for(int i = 0; i < (int)s.size(); ++i) {
        if(s[i] == '(') {
            if(!V.empty()) {
             	int u = V.top();
				T[u][T[u][0] > -1] = v; 
			}
            V.push(v++);    
        } else if(s[i] == ')') V.pop();
        else if(s[i] != ',') {
            int k = i;
            while(k < (int)s.size() && isdigit(s[k])) ++k;
            T[V.top()][T[V.top()][0] > -1] = v;
            string p(s.begin() + i, s.begin() + k);
            R[stoi(p) - 1] = v++;
            i = k - 1;
        }
    }
	return cnt;
}

int lca(int a, int b) {
	if(lv[a] > lv[b]) swap(a, b);
	int dist = lv[b] - lv[a];
	int z = 31 - __builtin_clz(B);
	for(int k = z; k >= 0; --k) {
		if((1 << k) <= dist) {
			dist -= 1 << k;
			b = sp[k][b];
		}
	}
	if(a == b) return a;
	for(int k = z; k >= 0; --k) {
		if(sp[k][a] != sp[k][b]) {
			a = sp[k][a];
			b = sp[k][b];
		}
	}
	return sp[0][a];
}

void dfsB(int u, int p) {
	sp[0][u] = p;
	sub[u] = TB[u][0] == -1 && TB[u][1] == -1;
	for(int k = 0; k < 2; ++k) {
		int v = TB[u][k];
		if(v != -1) {
			lv[v] = 1 + lv[u];
			dfsB(v, u);
			sub[u] += sub[v];
		}
	}
}

void dfsA(int u) {
	int p = TA[u][0], q = TA[u][1];
	sz[u] = 0;
	if(p == -1 && q == -1) {
		++ans;
		sz[u] = 1;
		return;
	} else if(p == -1) {
		dfsA(q);
		LCA[u] = LCA[q];
		sz[u] = sz[q];
	} else if(q == -1) {
		dfsA(p);
		LCA[u] = LCA[p];
		sz[u] = sz[p];
	} else {
		dfsA(p);		
		dfsA(q);
		sz[u] = sz[p] + sz[q];
		LCA[u] = lca(LCA[p], LCA[q]);
		if(sub[LCA[u]] == sz[u]) ++ans;
	}
}

void solve() {
    cin >> n >> a >> b;
    A = init(TA, RA, a);
    B = init(TB, RB, b);
    sz.resize(B);
	LCA.resize(A);
	lv.resize(B);
	sub.resize(B);
	lv[0] = 0;
	dfsB(0, 0);
	int z = 31 - __builtin_clz(B);
	for(int k = 1; k <= z; ++k)
		for(int i = 0; i < B; ++i)
			sp[k][i] = sp[k - 1][sp[k - 1][i]];
	for(int k = 0; k < n; ++k)
		LCA[RA[k]] = RB[k];
	dfsA(0);
	cout << ans << '\n';
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}