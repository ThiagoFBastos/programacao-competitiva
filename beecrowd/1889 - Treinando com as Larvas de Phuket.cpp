#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

double area(double a, double b, double c) {
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	cout.precision(2);
	cout.setf(ios_base :: fixed);
	while(t--) {
		int n;
		cin >> n;
		vector<double> a(n);
		for(int i = 0; i < n; ++i) cin >> a[i];
		sort(a.begin(), a.end());
		double ans = INT_MAX;
		for(int i = 0; i < n - 2; ++i) {
			int lo = i + 1;
			for(int j = i + 1; j < n - 1; ++j) {
				while(lo < n && a[i] + a[j] > a[lo]) ++lo;
				if(lo > j + 1) ans = min(ans, area(a[i], a[j], a[lo - 1]));
				if(a[i] + a[j] > a[j + 1]) ans = min(ans, area(a[i], a[j], a[j + 1]));
			}
		}
		if(ans == INT_MAX) cout << -1 << '\n';
		else cout << ans << '\n';
	}
	return 0;
}