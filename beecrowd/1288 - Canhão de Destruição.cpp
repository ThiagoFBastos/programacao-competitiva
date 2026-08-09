#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e2 + 5, INF = 1e9;

int dp[N];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int t;

	cin >> t;

	while(t-- > 0) {
		int n, cap, res;

		cin >> n;

		vector<pair<int, int>> weapon(n);

		for(auto& [power, weight] : weapon)
			cin >> power >> weight;

		cin >> cap >> res;

		fill(dp, dp + cap + 1, -INF);
		dp[0] = 0;

		for(const auto& [power, weight] : weapon)
			for(int i = cap - weight; i >= 0; --i)
				dp[i + weight] = max(dp[i + weight], dp[i] + power);
		
		int destroy = *max_element(dp, dp + cap + 1);

		if(destroy >= res)
			cout << "Missao completada com sucesso\n";
		else
			cout << "Falha na missao\n";
	}

	return 0;
}