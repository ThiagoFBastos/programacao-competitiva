#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")
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
const int maxn = 40001;
int n, f, a[40];
char sig[41];
ll mask1[maxn], mask2[maxn];
bool vis[maxn];
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while(true) {
		int soma = 0;
		cin >> n >> f;
		if(!(n || f)) break;
		for(int i = 0; i < n; ++i) {
			cin >> a[i];
			soma -= a[i];
		}
		if(soma == f) 
			cout << string('-', n) << '\n';
		else if((soma - f) & 1) 
			cout << "*\n";		
		else {
			memset(mask1, 0, sizeof mask1);
			memset(mask2, 0, sizeof mask2);
			memset(vis, false, sizeof vis);
			vis[0] = true;
			int x = (f - soma) / 2;
			for(int i = 0; i < n; ++i) {
				if(a[i] > x) continue;
				for(int k = x - a[i]; k >= 0; --k) {
					if(vis[k]) {
						ll y = mask1[k] | 1LL << i;
						if(vis[k + a[i]])
							mask1[k + a[i]] &= y;
						else
							mask1[k + a[i]] = y;
						mask2[k + a[i]] |= mask2[k] | 1LL << i;
						vis[k + a[i]] = true;
					}
				}
			}
			if(vis[x]) {
				memset(sig, '\0', sizeof sig);
				for(int i = 0; i < n; ++i) {
					if(mask1[x] & 1LL << i) sig[i] = '+';
					else if(mask2[x] & 1LL << i) sig[i] = '?';
					else sig[i] = '-';
				}
				cout << sig << '\n';
			}
			else 
				cout << "*\n";
		}
	}
	return 0;
}