#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
    int l, w, h, delta;

	const double pi = acos(-1);

	while(cin >> l >> w >> h >> delta) {

		double side = l * tan(delta * pi / 180.0);
		double volume;

		if(side <= h)
			volume = 1.0 * l * w * h - side * w * l / 2.0;
		else
		{
			side = h * tan((90.0 - delta) * pi / 180.0);

			volume = side * h * w / 2.0;
		}

		cout << fixed << setprecision(3) << volume << " mL\n";
	}

	return 0;
}