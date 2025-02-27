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

typedef complex<double> base;

void fft(vector<base>& a, bool invert) {
	int n = a.size();
	
	for(int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for(; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	for(int len = 2; len <= n; len <<= 1) {
		double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for(int i = 0; i < n; i += len) {
			base w(1);
			for(int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}

	for(int i = 0; invert && i < n; ++i)
		a[i] /= n;
}

vector<base> convolution(vector<base>& a, vector<base>& b) {
	int n = 1 << (33 - __builtin_clz(a.size() + b.size()));
	a.resize(n);
	b.resize(n);
	fft(a, false);
	fft(b, false);
	vector<base> res(n);
	for(int i = 0; i < n; ++i) res[i] = a[i] * b[i];
	fft(res, true);
	return res;
}

const int N = 666 + 10;

int land[N][N], layout[N][N];
i64 sumLand[N][N], sumLayout;
i64 sqrLand[N][N], sqrLayout;

void upd(i64 a[][N], i64 v, int x0, int y0, int x1, int y1) {
	a[x0][y0] += v;
	a[x1 + 1][y1 + 1] += v;
	a[x0][y1 + 1] -= v;
	a[x1 + 1][y0] -= v;
}

void build(i64 a[][N], int x, int y) {
	a[x][y] += a[x - 1][y];
	a[x][y] += a[x][y - 1];
	a[x][y] -= a[x - 1][y - 1];
}

void solve() {
	int r, c;
	int h, w;
	int x, y;
	int k;

	cin >> r >> c;

	vector<base> P((r + 1) * (c + 1)), Q((r + 1) * (c + 1));

	for(int i = 1; i <= r; ++i) {
		for(int j = 1; j <= c; ++j) {
			cin >> land[i][j];
			P[i * c + j] = land[i][j];
		}
	}

	cin >> h >> w;

	for(int i = 1; i <= h; ++i) {
		for(int j = 1; j <= w; ++j) {
			cin >> layout[i][j];
			Q[(h - i) * c + w - j] = layout[i][j];
			sumLayout += layout[i][j];
			sqrLayout += layout[i][j] * layout[i][j];
		}
	}

	for(int i = 1; i <= r; ++i) {
		for(int j = 1; j <= c; ++j) {
			int x = max(1, i - h + 1), y = max(1, j - w + 1);
			upd(sumLand, land[i][j], x, y, i, j);
			upd(sqrLand, land[i][j] * land[i][j], x, y, i, j);
		}
	}

	for(int i = 1; i <= r; ++i)
	for(int j = 1; j <= c; ++j) {
		build(sumLand, i, j);
		build(sqrLand, i, j);
	}

	cin >> x >> y;
	cin >> k;

	auto R = convolution(P, Q);	

	vector<tuple<i64, int, int>> best;

	for(int i = 1; i <= r - h + 1; ++i) {
		for(int j = 1; j <= c - w + 1; ++j) {
			int res = land[i + x - 1][j + y - 1];
			i64 score = res * res * h * w;
			score -= 2 * (sumLand[i][j] - sumLayout) * res;
			score += sqrLand[i][j];
			score += sqrLayout;
			score -= 2 * (i64)round(R[(i - 1 + h) * c + (w + j - 1)].real());
			best.pb({score, i, j});
		}
	}

	sort(all(best));

	for(int i = 0; i < k; ++i) {
		i64 s;
		int x, y;
		tie(s, x, y) = best[i];
		cout << x << ' ' << y << ' ' << s << '\n';
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
