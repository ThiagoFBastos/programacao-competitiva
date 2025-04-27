#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("mmx,sse,sse2")

#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n, k;
	ll s = 0;
	
	cin >> n >> k;

	vi a(n);

	for(int i = 0; i < n; ++i) {
		cin >> a[i];
		s += a[i];
	}

	if(k >= n) 
		cout << s << '\n';
	else {
		priority_queue<int, vi, greater<int>> pq;
		int t = 0;
		s = 0;
		for(int i = 0; i < k; ++i) 
			s += a[i];
		t = k;
		pq.push(a[k]);
		for(int i = k + 1; i < n; ++i) {
			if(t >= (1LL + pq.size()) * k)
				pq.push(a[i]);
			else if(pq.top() < a[i]) {
				++t;
				s += pq.top();
				pq.pop();
				pq.push(a[i]);
			} else {
				++t;
				s += a[i];
			}
		}
		cout << s << '\n';
	} 
	return 0;
}