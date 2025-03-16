#include "bits/stdc++.h"
using namespace std;
int contig(vector<int>& a) {
	multiset<int> S;
	int n = size(a), k = n - 1, ans = 0;
	if(n < 3) return 0;
	S.insert(a[n - 1]);
	S.insert(a[n - 2]);
	for(int i = n - 3; i >= 0; --i) {
		S.insert(a[i]);
		while(int(size(S)) >= 3) {
			int x = *S.begin(), y = *next(S.begin()), z = *S.rbegin();
			if(x + y > z) break;
			S.erase(S.find(a[k]));
			--k;
		}
		if(int(size(S)) >= 3) ans = max(ans, int(size(S)));
	}
	return ans;
}
int subseq(vector<int>& a) {
	sort(a.begin(), a.end());
	return contig(a);
}
void solve() {	
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; ++i) cin >> a[i];
	cout << contig(a) << '\n';
	cout << subseq(a) << '\n';
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}