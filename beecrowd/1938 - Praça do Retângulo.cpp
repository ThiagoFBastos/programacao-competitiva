#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 3e3;
	int n;
	pair<int, int> p[MAXN];
	cin >> n;
	for(int k = 0; k < n; ++k)
		cin >> p[k].X >> p[k].Y;
	sort(p, p + n);
	long long r = 0;
	for(int k = 0; k < n; ++k) {
		int h_min = INT_MAX, h_max = INT_MIN;
		for(int i = k - 1; i >= 0 && h_min > h_max; --i) {
			if(p[i].Y > p[k].Y && p[i].Y < h_min)
				++r, h_min = p[i].Y;
			else if(p[i].Y < p[k].Y && p[i].Y > h_max)
				++r, h_max = p[i].Y;
		}
	}
	cout << r << '\n';
	return 0;
}