#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
#define x first
#define y second
 
bool cmp(ii L, ii R) {
 
	return L.y < R.y;
}
 
int main() {
 
	int n;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
 
	vii t(n);
	vi cmax(n);
 
	for(int k = 0; k < n; ++k)
		cin >> t[k].x >> t[k].y;
 
	sort(t.begin(), t.end(), cmp);
 
	cmax[0] = 1;
 
	for(int k = 1; k < n; ++k) {
 
		int j = upper_bound(t.begin(), t.end(), make_pair(0, t[k].x), cmp) - t.begin() - 1;
 
		if(j >= 0)
			cmax[k] = 1 + cmax[j];
 
		else
			cmax[k] = 1;
 
		cmax[k] = max(cmax[k], cmax[k - 1]);		
	}
 
	cout << cmax.back() << '\n';
 
	return 0;
}
