#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

const int maxn = 100;
double pe[maxn], pc[maxn];
int ev1, ev2, at, d, pa[maxn];

void solve(int e, int pai) {
	if(e == pai) pc[e] = 1.0;
	pa[e] = pai;
	pe[e] = 0;
	if(e > d && e - d != pai) {
		pc[e - d] = (6.0 - at) * pc[e] / 6.0;
		solve(e - d, e);
		pe[e] += at * (6.0 - at) * pe[e - d] / 36.0;
	}
	if(e + d != pai) {
		if(e + d < ev1 + ev2) {
			pc[e + d] = at * pc[e] / 6.0;
			solve(e + d, e);
			pe[e] += at * (6.0 - at) * pe[e + d] / 36.0;
		} else {
			pc[e + d] = at * pc[e] / 6.0;
			pa[e + d] = e;
		}
	}
	pe[e] = 1.0 / (1.0 - pe[e]);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cout.precision(1);
	cout.setf(ios_base :: fixed);
	while(true) {
		cin >> ev1 >> ev2 >> at >> d;
		if(ev1 == 0) break;
		solve(ev1, ev1);
		vector<int> path;
		for(int v = ev1 + (ev2 + d - 1) / d * d; v != ev1; v = pa[v]) path.push_back(v);
		path.push_back(ev1);
		reverse(path.begin(), path.end());
		double pct = 1;
		for(int k = 0; k < (int)path.size() - 1; ++k) pct = at * pct * pe[path[k]] / 6.0; 
		cout << 100 * pct << '\n';
	}
	return 0;
}
