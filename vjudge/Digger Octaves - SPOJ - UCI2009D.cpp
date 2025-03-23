#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define INF   1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
using i128 = __int128;

template <class K, class V>
using ht = gp_hash_table
<K, V, std :: hash<K>, std :: equal_to<K>,
direct_mask_range_hashing<>,
linear_probe_fn<>,
hash_standard_resize_policy<
hash_exponential_size_policy<>,
hash_load_check_resize_trigger
<>, true>>;

const int N = 8;

bitset<N*N> flag;
ht<bitset<N*N>, null_type> us;
char table[N][N+1];
int n, cnt;
ii delta[] = {{1,0},{0,-1},{-1,0},{0,1}};

void backtrack(int k, int x, int y) {
	if(k == 8) {cnt += us.insert(flag).sc; return;}
	if(x < 0 || x >= n || y < 0 || y >= n || flag[x*n+y] || table[x][y] == '.') return;
	flag[x*n+y] = 1;
	for(auto& D : delta) backtrack(k+1,x+D.fi,y+D.sc);
	flag[x*n+y] = 0;
}

int main(int argc, char* argv[]) {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int t;

	cin >> t;

	while(t--) {
		cin >> n;
		for(int i = 0; i < n; ++i) cin >> table[i];
		us.clear(); cnt = 0;
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			backtrack(0, i, j);
		cout << cnt << '\n';
	}

	return 0;
}