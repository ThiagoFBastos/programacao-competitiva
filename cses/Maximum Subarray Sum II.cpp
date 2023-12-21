#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
 
	int n, a, b;
 
	cin >> n >> a >> b;
 
	vi x(n);
	vector<ll> preffix(n + 1);
	ll maxsum = LLONG_MIN;
 
	preffix[0] = 0;
 
	for(int k = 0; k < n; ++k) {
 
		cin >> x[k];
 
		preffix[k + 1] = x[k] + preffix[k];
	}
		
	deque<int> Q;
 
	Q.push_back(0);
 
	for(int k = a; k <= n; ++k) {
 
		maxsum = max(maxsum, preffix[k] - preffix[Q.front()]);
 
		while(!Q.empty() && Q.front() <= k - b)
			Q.pop_front();
 
		while(!Q.empty() && preffix[Q.back()] >= preffix[k - a + 1])
			Q.pop_back();
 
		Q.push_back(k - a + 1); 		
	}
 
	cout << maxsum << '\n';
 
	return 0;
}
