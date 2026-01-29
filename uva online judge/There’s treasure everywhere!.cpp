#include "bits/stdc++.h"

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	double d = sqrt(2.0) / 2.0;

	unordered_map<string, pair<double, double>> directions = {
		{"N", {0.0, 1.0}},
		{"NE", {d, d}},
		{"E", {1.0, 0.0}},
		{"SE", {d, -d}},
		{"S", {0.0, -1.0}},
		{"SW", {-d, -d}},
		{"W", {-1.0, 0.0}},
		{"NW", {-d, d}}
	};

	int tc = 1;

	for(string text; cin >> text; ++tc) {

		if(text == "END")
			break;

		replace_if(text.begin(), text.end(), [](char c) { return c == ',' || c == '.';}, ' ');

		double x = 0, y = 0;

		istringstream is(text);

		for(string s; is >> s; ) {
			auto it = find_if(s.begin(), s.end(), [](char c) { return !isdigit(c);});

			string delta(s.begin(), it);
			string dir(it, s.end());

			int number = stoi(delta);
			double delta_x, delta_y;

			tie(delta_x, delta_y) = directions[dir];

			x += number * delta_x;
			y += number * delta_y;
		}

		cout << "Map #" << tc << '\n';
		cout << fixed << setprecision(3) << "The treasure is located at (" << x << "," << y << ").\n";
		cout << fixed << setprecision(3) << "The distance to the treasure is " << hypot(x, y) << ".\n";
		cout << '\n';
	}

	return 0;
}