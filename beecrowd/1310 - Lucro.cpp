#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, cd;
	while(cin >> n) {
		int ans = 0, soma = 0;
		cin >> cd;
		for(int k = 0; k < n; ++k) {
			int custo;
			cin >> custo;
			soma += custo - cd;
			ans = max(soma, ans);
			if(soma < 0) soma = 0;
		}
		cout << ans << '\n';
	}
	return 0;
}