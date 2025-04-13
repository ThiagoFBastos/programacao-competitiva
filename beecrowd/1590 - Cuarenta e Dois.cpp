#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define EPS 1e-9
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int t, a[35];
	cin >> t;
	while(t--) {
		int n, q;
		cin >> n >> q;
		for(int i = 0; i < n; ++i) cin >> a[i];
		int ans = 0;
		for(int k = 30; k >= 0; --k) {
			int cnt = 0;
			for(int j = 0; j < n; ++j) if(a[j] & (1 << k)) ++cnt;
			if(cnt >= q) {
				int i = 0;
				ans |= 1 << k;	
				for(int j = 0; j < n; ++j) if(a[j] & (1 << k)) a[i++] = a[j];
				n = i;
			}
		}
		cout << ans << '\n';
	}
    return 0;
}