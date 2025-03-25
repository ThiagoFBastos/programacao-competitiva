#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int MAXN = 410;

int tc;

char g[MAXN][MAXN];
bool vis[MAXN][MAXN];

ii delta[] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

int r, c;

char dir[] = "SENW";

vector<ii> X[2][2][4];

bool connected() {
	int cells = 0;
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			cells += g[i][j] == '*';
			vis[i][j] = g[i][j] == '#';
		}
	}
	function<void(int, int)> dfs = [&](int i, int j) {
		if(vis[i][j]) return;
		vis[i][j] = true;
		--cells;
		if(i) dfs(i - 1, j);
		if(i < r - 1) dfs(i + 1, j);
		if(j) dfs(i, j - 1);
		if(j < c - 1) dfs(i, j + 1);
	};

	dfs(0, 0);

	return cells == 0;
}

vector<ii> ord;

void build(int i, int j, int d) {
	if(vis[i][j]) return;

	int x0 = i - i % 2, y0 = j - j % 2;

	for(int dx = 0; dx < 2; ++dx)
	for(int dy = 0; dy < 2; ++dy)
		vis[x0 + dx][y0 + dy] = true;

	auto& K = X[i % 2][j % 2][d];

	for(int k = 0; k < (int)K.size(); ++k) {
		auto [dx, dy] = K[k];
		int x = x0 + dx, y = y0 + dy;
		ord.emplace_back(x, y);
		for(int l = 0; l < 4; ++l) {
			auto [dx, dy] = delta[l];
			int _x = x + dx, _y = y + dy;
			if(_x < 0 || _y < 0 || _x >= r || _y >= c || vis[_x][_y]) continue;
			build(_x, _y, l);
		}
	}
}

void solve() {

	cin >> r >> c;

	for(int i = 0; i < r; ++i) {
		string row;
		cin >> row;
		for(int j = 0; j < c; ++j) {
			for(int dx = 0; dx < 2; ++dx)
			for(int dy = 0; dy < 2; ++dy)
				g[2 * i + dx][2 * j + dy] = row[j];
		}
	}

	r *= 2;
	c *= 2;

	cout << "Case #" << ++tc << ": ";

	if(!connected()) {
		cout << "IMPOSSIBLE\n";
		return;
	}

	X[0][0][0] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
	X[0][0][1] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}};

	X[0][1][0] = {{0, 1}, {1, 1}, {1, 0}, {0, 0}};
	X[0][1][3] = {{0, 1}, {0, 0}, {1, 0}, {1, 1}};

	X[1][0][2] = {{1, 0}, {0, 0}, {0, 1}, {1, 1}};
	X[1][0][1] = {{1, 0}, {1, 1}, {0, 1}, {0, 0}};

	X[1][1][2] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};
	X[1][1][3] = {{1, 1}, {1, 0}, {0, 0}, {0, 1}};
	
	for(int i = 0; i < r; ++i)
	for(int j = 0; j < c; ++j)
		vis[i][j] = g[i][j] == '#';

	ord.clear();
	build(0, 0, 0);

	string ans;

	ord.emplace_back(0, 0);

	int m = ord.size();
	string s;

	for(int i = 0; i < m; ++i) {
		auto [x0, y0] = ord[i - 1];
		auto [x1, y1] = ord[i];
		x1 -= x0, y1 -= y0;
		for(int j = 0; j < 4; ++j) {
			if(delta[j] == ii(x1, y1)) {
				s += dir[j];
				break;
			}
		}
	}

	cout << s << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	while(t--) solve();
	return 0;
}