#include "bits/stdc++.h"
 
using namespace std;
 
#define INF 2000000100
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
 
void solve() {
	
	int n;
 
	cin >> n;
	
	n <<= 1;
 
	vector<int> a(n), b(n);
	vector<int> lisA(n), lisB(n);
	vector<int> mnA(n), mxA(n);
	vector<int> mnB(n), mxB(n);
 
	for(int& v : a) cin >> v;
	for(int& v : b) cin >> v;
 
	lisA.back() = lisB.back() = 1;
	mnA.back() = mxA.back() = -1;
	mnB.back() = mxB.back() = 1;
 
	auto func = [&](int& lis, int& mn, int& mx, int i, int v, int x) {
		if(min(a[i + 1], b[i + 1]) >= v) {
			lis = 1 + max(lisA[i + 1], lisB[i + 1]);
			if(lisA[i + 1] == lisB[i + 1]) {
				mn = min(mnA[i + 1], mnB[i + 1]) + x;
				mx = max(mxA[i + 1], mxB[i + 1]) + x;
			} else if(lisA[i + 1] > lisB[i + 1]) {
				mn = mnA[i + 1] + x;
				mx = mxA[i + 1] + x;
			} else {
				mn = mnB[i + 1] + x;
				mx = mxB[i + 1] + x;
			}
		} else if(a[i + 1] >= v) {
			lis = 1 + lisA[i + 1];
			mn = mnA[i + 1] + x;
			mx = mxA[i + 1] + x;
		} else if(b[i + 1] >= v) {
			lis = 1 + lisB[i + 1];
			mn = mnB[i + 1] + x;
			mx = mxB[i + 1] + x;
		} else {
			lis = 1;
			mn = mx = x;
		}
	};
 
	for(int i = n - 2; i >= 0; --i) {
		func(lisA[i], mnA[i], mxA[i], i, a[i], -1);
		func(lisB[i], mnB[i], mxB[i], i, b[i], 1);
	}
 
	if((lisA[0] != n || mnA[0] > 0 || mxA[0] < 0) && (lisB[0] != n || mnB[0] > 0 || mxB[0] < 0)) {
		cout << "-1\n";
		return;
	}
 
	string t;
	int prv = 0, diff = 0;
 
	for(int i = 0; i < n; ++i) {
		if(min(a[i], b[i]) >= prv) {
			if(lisA[i] >= lisB[i] && diff + mnA[i] <= 0 && diff + mxA[i] >= 0) {
				--diff;
				prv = a[i];
				t += 'A';
			} else {
				++diff;
				prv = b[i];
				t += 'B';
			}
		} else if(a[i] >= prv) {
			--diff;
			prv = a[i];
			t += 'A';
		} else {
			++diff;
			prv = b[i];
			t += 'B';
		}
	}
 
	cout << t << '\n';	
}	
 
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}
