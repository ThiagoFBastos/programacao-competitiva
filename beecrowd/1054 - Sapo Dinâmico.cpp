#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

/*
	. tem caminho
	. não pode ter uma pedra pequena que todo caminho passa por ela
*/

	int t;

	cin >> t;

	auto can_cross_river = [](const auto& stones, int jump) {
		const auto n = static_cast<int>(stones.size());
		int hi = 1;
		vector<int> freq(n + 1, 0);
		
		for(int i = 0; i < n; ++i) {
			const auto& [big, d] = stones[i];

			if(i >= hi)
				return false;

			while(hi < n && d + jump >= stones[hi].second)
				++hi;

			if(i + 3 <= hi) {
				++freq[i + 2];
				--freq[hi];
			}
		}

		if(hi < n)
			return false;

		for(int i = 1; i <= n; ++i) {
			freq[i] += freq[i - 1];

			if(freq[i] == 0 && !stones[i - 1].first)
				return false;
		}

		return true;	
	};

	for(int i = 1; i <= t; ++i) {
		int n, d;

		cin >> n >> d;

		vector<pair<bool, int>> stones;

		stones.reserve(n + 2);

		stones.emplace_back(true, 0);

		for(int i = 0; i < n; ++i) {
			string str;
			char type;
			int dist;

			cin >> str;

			sscanf(str.c_str(), "%c-%d", &type, &dist);

			stones.emplace_back(type == 'B', dist);
		}

		stones.emplace_back(true, d);

		int lo = 0, hi = 1e9;

		while(lo < hi) {
			int mid = (lo + hi) / 2;

			if(can_cross_river(stones, mid))
				hi = mid;
			else
				lo = mid + 1;
		}

		cout << "Case " << i << ": " << hi << '\n';
	}

	return 0;
}