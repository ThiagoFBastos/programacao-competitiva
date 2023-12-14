#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 1000000000
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
 
const int N = 1e6 + 10;
 
int v[N], tmp[N], n;
 
void solve() {
	int mx = 0, ans = 0;
 
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		cin >> v[i];
		mx = max(mx, v[i]);
	}
 
	mx <<= 1;
 
	int lg = 0;
 
	while((1 << lg) <= mx) ++lg;
 
	sort(v, v + n);
 
	for(int i = lg - 1; i >= 0; --i) {
		int lo[2] = {n, n}, hi[2] = {n, n};
		int L[2] = {1<<i, (1<<i)+(1<<(i+1))}, U[2] = {(1<<(i+1))-1, (1<<(i+2))-1};
		int pairs = 0, mask = (1 << (i + 1)) - 1;
 
		int k = 0, mid = 0, l = 0;
 
		while(mid < n && ~v[mid] & (1 << (i + 1))) ++mid;
 
		for(int i = 0; i < n; ++i) v[i] &= mask;
 
		int j = mid;
 
		while(k < mid && j < n) tmp[l++] = v[k] < v[j] ? v[k++] : v[j++];
 
		while(k < mid) tmp[l++] = v[k++];
 
		while(j < n) tmp[l++] = v[j++];
 
		memcpy(v, tmp, sizeof(int) * n);
 
		for(int j = 0; j < n; ++j) {
			for(int k = 0; k < 2; ++k) {
				while(hi[k] && v[j] + v[hi[k] - 1] > U[k]) --hi[k];
				while(lo[k] && v[j] + v[lo[k] - 1] >= L[k]) --lo[k];
				pairs ^= max(0, hi[k] - max(j, lo[k]));
			}
		}
 
		ans ^= (pairs & 1) * (1 << i);
	}
 
	cout << ans << '\n';
}
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
