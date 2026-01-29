#include "bits/stdc++.h"

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int t;
	
	cin >> t;

	for(int i = 0; i < t; ++i) {
		size_t n;

		cin >> n;

		unordered_map<int, vector<int>> points;

		for(size_t j = 0; j < n; ++j) {
			int x, y;

			cin >> x >> y;

			points[y].push_back(x);
		}

		int min_x = numeric_limits<int>::max();
		int max_x = numeric_limits<int>::min();

		for(auto& line : points) {
			auto& coords = line.second;

			sort(coords.begin(), coords.end());

			auto m = coords.size();

			for(int l = 0, r = m - 1; l <= r; ++l, --r) {
				int x = coords[l] + coords[r];

				min_x = min(min_x, x);
				max_x = max(max_x, x);
			}
		}
		
		cout << (min_x == max_x ? "YES\n" : "NO\n");
	}

	return 0;
}