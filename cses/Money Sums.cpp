#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse,sse2")
#define f first
#define s second
using namespace std;
using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<bool> coins(1000 * n + 1, false);
	coins[0] = true;
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		for(int k = 1000 * (i + 1) - x; k >= 0; --k)
			coins[k + x] = coins[k + x] | coins[k];
	}
	int ct = 0;
	for(bool c : coins) ct += c;
	cout << ct - 1 << '\n';
	for(int i = 1; i <= coins.size(); ++i)
		if(coins[i]) cout << i << ' ';
	cout << '\n';
	return 0;
} 
