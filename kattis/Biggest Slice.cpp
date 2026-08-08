#include "bits/stdc++.h"

using namespace std;

using T = tuple<int, int, int>;

double rad(int a, int b, int c) {
	double deg = a + b / 60.0 + c / 3600.0;
	return deg * acos(-1) / 180.0;
}

void solve() {
	int n, r, a, b, c, x, y, z;
	set<T> s;
		
	cin >> r >> n >> a >> b >> c;
	
	if(n == 1) {
		cout << fixed << setprecision(8) << pow(r, 2) * acos(-1) << '\n';
		return;
	}
	
	x = y = z = 0;
	
	for(int k = 0; k < n; ++k) {
		z = z + c;
		y = b + y + z / 60;
		z %= 60;
		x = a + x + y / 60;
		y %= 60;
		x %= 360;
		if(!s.insert({x, y, z}).second) break;
	}
	
	vector<double> ang;
	double slice = 0;
	
	while(!s.empty()) {
		auto [a, b, c] = *s.begin();
		s.erase(s.begin());
		ang.push_back(rad(a, b, c));
	}
	
	int m = ang.size();
	
	for(int i = 0; i < m; ++i) {
		int k = (i + 1) % m;	
		double theta = ang[k] - ang[i];
		if(theta < 0) theta += 2 * acos(-1);
		slice = max(slice, theta);
	}
	
	cout << fixed << setprecision(8) << slice * r * r / 2 << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
 	return 0;
}