#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
 
int main() {
 
	int n;
 
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
 
	cin >> n;
 
	vi l(n);
 
	for(int k = 0; k < n; ++k)
		cin >> l[k];
 
	sort(l.begin(), l.end());
 
	vector<ll> preffix(n + 1);
 
	for(int k = 1; k <= n; ++k)
		preffix[k] = l[k - 1] + preffix[k - 1];		
	
	long long minop = LLONG_MAX;
	
	for(int k = 1; k <= n; ++k)
		minop = min(minop, l[k - 1] * (2LL * k - n) + preffix.back() - 2LL * preffix[k]);
 
	cout << minop << '\n';
 
	return 0;
}
