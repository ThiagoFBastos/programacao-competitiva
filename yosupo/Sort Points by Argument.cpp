#include "bits/stdc++.h"

using namespace std;

using point = complex<long double>;

constexpr long double eps = 1e-9;

int half(point p) 
{
	return p.imag() >= 0;
}

bool cmp(point a, point b) 
{
	if(half(a) != half(b)) 
		return half(a) < half(b);

	auto cross = (conj(a) * b).imag();

	return cross > eps || (fabs(cross) < eps && a.real() > b.real());
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	
	int n;

	cin >> n;

	vector<point> points;

	points.reserve(n);

	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		if(!x && !y) 
			continue;

		points.emplace_back((long double)x, (long double)y);
	}

	sort(points.begin(), points.end(), cmp);
	
	size_t i = 0;

	while(i < points.size() && points[i].imag() < eps) 
		++i;

	points.insert(points.begin() + i, n - (int)points.size(), point(0, 0));

	for(const auto& p : points)
		cout << (int)p.real() << ' ' << (int)p.imag() << '\n';

	return 0;
}