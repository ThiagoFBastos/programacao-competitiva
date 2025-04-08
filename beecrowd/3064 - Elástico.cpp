#include "bits/stdc++.h"

using namespace std;

#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

struct point {
	int x, y;

	point() {x = y = 0;}
	point(int _x, int _y) : x {_x}, y {_y} {}

	i64 square_norm() const {
		return 1ll * x * x + 1ll * y * y;
	}

	bool operator<(point other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator>(point other) const {
		return x > other.x || (x == other.x && y > other.y);
	}

	bool operator<=(point other) const {
		return x < other.x || (x == other.x && y <= other.y);
	}

	bool operator>=(point other) const {
		return x > other.x || (x == other.x && y >= other.y);
	}

	bool operator==(point other) const {
		return x == other.x && y == other.y;
	}

	point operator+(point other) const {
		return {x + other.x, y + other.y};
	}

	point operator-(point other) const {
		return {x - other.x, y - other.y};
	}

	point operator*(int k) const {
		return {x * k, y * k};
	}

	point& operator*=(int k) {
		x *= k;
		y *= k;
		return *this;
	}

	point& operator+=(point other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	point& operator-=(point other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}

	point operator-() const {
		return {-x, -y};
	}
};

i64 cross(point p1, point p2) {
	return (i64)p1.x * p2.y - (i64)p1.y * p2.x;
}

bool cw(point p, point q, point r) {
	return cross(q - p, r - p) < 0;
}

const int N = 201;

int dp[N][N];

bool cmp(point a, point b) {
	return cross(a, b) < 0;
}

void solve() {

	int teste = 1;

	while(true) {
		int n;

		cin >> n;

		if(!n) break;

		vector<point> pt(n);

		for(int i = 0; i < n; ++i) cin >> pt[i].x >> pt[i].y;

		sort(all(pt), cmp);

		pt.insert(pt.begin(), {0,0});

		for(int i = 0; i <= n; ++i)
			for(int j = i + 1; j <= n; ++j)
				dp[i][j] = -INF;

		for(int i = 1; i <= n; ++i) dp[0][i] = 2;

		for(int i = 2; i <= n; ++i) {
			for(int k = 0; k < i; ++k) {
				for(int j = k + 1; j < i; ++j) {
					if(cw(pt[k], pt[j], pt[i]))
						dp[j][i] = max(dp[j][i], dp[k][j] + 1);
				}
			}
		}

		int ans = 0;

		for(int i = 0; i <= n; ++i)	
		for(int j = 0; j <= n; ++j)
			ans = max(ans, dp[i][j]);

		cout << "Teste " << teste++ << "\n";
		cout << ans << "\n\n";
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
 //	cin >> t;
	while(t--) solve();
	return 0;
}