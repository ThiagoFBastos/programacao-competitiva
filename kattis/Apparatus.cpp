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
const int maxn = 1001, mod = 1e6 + 3;
int cnt = 1, fat[maxn], L[maxn], S[maxn], n, m;
string a[maxn], b[maxn];
bool ok = true;
void solve(int, int, int);
void solve(int lo, int hi, int k) {
	if(!ok || lo == hi)
		return;
	else if(k == m) 
		cnt = (ll)cnt * fat[hi - lo] % mod; 
	else {
		int lL, lS, umL, umS, zeroL, zeroS;
		do
		{
			lL = lS = lo;
			umL = umS = zeroL = zeroS = 0;
			for(int i = lo; i < hi; ++i) {
				if(a[k][L[i]] == '0') {
					++zeroL;
					swap(L[lL++], L[i]);
				} else ++umL;
				if(b[k][S[i]] == '0') {
					++zeroS;
					swap(S[lS++], S[i]);
				} else ++umS;
			}
			++k;
			if(umL != umS || zeroL != zeroS) {
				ok = false;
				cnt = 0;
				break;
			}
		} while(k < m && (!zeroL || !umL));
		solve(lo, lL, k);
		solve(lL, hi, k);
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	fat[0] = 1;
	for(int k = 1; k < maxn; ++k) fat[k] = fat[k - 1] * (ll)k % mod;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) L[i] = S[i] = i;
	for(int i = 0; i < m; ++i) cin >> a[i] >> b[i];
	solve(0, n, 0);
	cout << cnt << '\n';
	return 0;
}