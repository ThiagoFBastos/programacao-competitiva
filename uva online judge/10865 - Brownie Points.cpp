#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	while(true) {
		int n;

		cin >> n;

		if(!n) break;

		using pt = pair<int, int>;
		vector<pt> points(n);

		for(auto& p : points)
			cin >> p.first >> p.second;

		auto mid_point = points[n / 2];

		transform(points.begin(), points.end(), points.begin(), [&](pt p) {
			p.first -= mid_point.first;
			p.second -= mid_point.second;
			return p;
		});

		int stan_points = count_if(points.begin(), points.end(), [](pt p) {
			return (p.first > 0 && p.second > 0) || (p.first < 0 && p.second < 0);
		});

		int ollie_points = count_if(points.begin(), points.end(), [](pt p) {
			return (p.first > 0 && p.second < 0) || (p.first < 0 && p.second > 0);
		});

		cout << stan_points << ' ' << ollie_points << '\n';
	}

	return 0;
}