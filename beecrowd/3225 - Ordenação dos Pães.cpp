#include "bits/stdc++.h"
using namespace std;
vector<int> t;
int merge(vector<int>& a, int L, int R) {
	int i = L, j = L, k, mid = (L + R) / 2, ans = 0;
	k = mid + 1;
	while(i <= mid && k <= R) {
		if(a[i] < a[k]) t[j++] = a[i++];
		else ans ^= (mid - i + 1) & 1, t[j++] = a[k++];
	}
	while(i <= mid) t[j++] = a[i++];
	while(j <= R) t[j++] = a[k++];
	for(; L <= R; ++L) a[L] = t[L];
	return ans;
}
int merge_sort(vector<int>& a, int L, int R) {
	if(L == R) return 0;
	int mid = (L + R) / 2;
	return merge_sort(a, L, mid) ^ merge_sort(a, mid + 1, R) ^ merge(a, L, R);
}
int parity(vector<int>& p) {
	t.resize(size(p));
	return merge_sort(p, 0, size(p) - 1);
}
void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 0; i < n; ++i) cin >> b[i];
	cout << (parity(a) == parity(b) ? "Possible\n" : "Impossible\n");
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}