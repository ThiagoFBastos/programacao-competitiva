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

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	int K, n, j = 0;	
	long long cnt = 0;
	cin >> s >> K;
	n = s.size();
	for(int i = 1; i <= n; ++i) {
		if(s[i - 1] == 'E') j = i;
		if(j == 0) continue;
		cnt += max(0, j - max(0, i - K));
	}
	for(int i = 1; i < n; ++i) {
		if(s[i - 1] == 'E') j = i + n;
		if(j == 0) continue;
		cnt += max(0, j - n - i + K);
		if(j > n) cnt -= max(0, j - max(n, n + i - K));
	}
	cout << cnt << '\n';
	return 0;
}