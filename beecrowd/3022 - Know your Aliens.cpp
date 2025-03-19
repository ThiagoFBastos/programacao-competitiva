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

void solve(string& s) {
	int low = 0, high = (int)s.size() - 1;
	while(low < s.size() && s[low] == s[0]) ++low;
	while(high >= 0 && s[high] == s.back()) --high;
	if(high < 0) cout << "0\n" << (s[0] == 'A' ? "-1\n" : "1\n");
	else if(low > high) {
		cout << "1\n";
		if(s[0] == 'A') cout << "1 " << -2 * low - 1 << '\n';
		else cout << "-1 " << 2 * low + 1 << '\n';
	}
	else {
		vector<int> R;
		long long c[23];
		int x = 1;
		memset(c, 0, sizeof c);
		if(s[high] == 'A')
			R.push_back(-2 * low - 1);	
		else {
			x = -1;
			R.push_back(2 * low + 1);
		}
		while(high >= low) {
			if(s[high] != s[high + 1])
				R.push_back(-2 * (high + 1) - 1);
			--high;
		}
		assert(R.size() < 23);
		int K = 1 << R.size();
		cout << R.size() << '\n';
		for(int k = 0; k < K; ++k) {
			long long ci = 1;
			int y = x;
			for(int i = 0; i < R.size(); ++i) {
				if(k & 1 << i) {
					if(R[i] > 0) y *= -1;
					ci *= R[i];
				}
			}
			c[(int)R.size() - __builtin_popcount(k)] += y * ci;
		}
		for(int i = R.size(); i > 0; --i) cout << c[i] << ' ';
		cout << c[0] << '\n';
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s;
	cin >> s;	
	solve(s);
	return 0;
}