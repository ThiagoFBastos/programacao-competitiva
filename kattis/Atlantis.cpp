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

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k = 0;
	ll t = 0;
	cin >> n;
	vii p(n);
	for(int i = 0; i < n; ++i)
		cin >> p[i].second >> p[i].first;
	sort(p.begin(), p.end());
	priority_queue<int> pq;
	for(int i = 0; i < n; ++i) {
		if(t + p[i].second <= p[i].first) {
			++k;
			t += p[i].second;
			pq.push(p[i].second);
		} else if(!pq.empty() && p[i].second <= pq.top() && t - pq.top() + p[i].second <= p[i].first) {
			t += p[i].second - pq.top();
			pq.pop();
			pq.push(p[i].second);	
		}
	}
	cout << k << '\n';
	return 0;
}

