#pragma GCC target ("sse,sse2")
#include <bits/stdc++.h>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

int st[1024][1024];

void update_x(int, int, int, int = 0, int = 500, int = 1);
void update_y(int, int, int, int = 0, int = 500, int = 1);
int query_x(int, int, int, int, int = 0, int = 500, int = 1);
int query_y(int, int, int, int = 0, int = 500, int = 1);

void update_x(int r, int c, int x, int lox, int hix, int nox) {
	if(lox != hix) {
		int mid = (lox + hix) >> 1;
		r <= mid ? update_x(r, c, x, lox, mid, nox << 1) : update_x(r, c, x, mid + 1, hix, nox << 1 | 1);	
	}
	update_y(c, x, nox);
}

void update_y(int c, int x, int nox, int loy, int hiy, int noy) {
	if(loy == hiy)
		st[nox][noy] += x;
	else {
		int mid = (loy + hiy) >> 1;
		c <= mid ? update_y(c, x, nox, loy, mid, noy << 1) : update_y(c, x, nox, mid + 1, hiy, noy << 1 | 1);
		st[nox][noy] = st[nox][noy << 1] + st[nox][noy << 1 | 1];
	}
}

int query_x(int lx, int rx, int ly, int ry, int lox, int hix, int nox) {
	if(lx > rx) return 0;
	else if(rx - lx == hix - lox) return query_y(ly, ry, nox);
	int mid = (lox + hix) >> 1;
	return query_x(lx, min(rx, mid), ly, ry, lox, mid, nox << 1) + 
	query_x(max(mid + 1, lx), rx, ly, ry, mid + 1, hix, nox << 1 | 1);
}

int query_y(int ly, int ry, int nox, int loy, int hiy, int noy) {
	if(ly > ry) return 0;
	else if(ry - ly == hiy - loy) return st[nox][noy];
	int mid = (loy + hiy) >> 1;
	return query_y(ly, min(mid, ry), nox, loy, mid, noy << 1) +
	query_y(max(ly, mid + 1), ry, nox, mid + 1, hiy, noy << 1 | 1);
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int Q;
	cin >> Q;
	while(Q--) {
		char t;
		int a, b, c, d, e;
		cin >> t >> a >> b;
		--a, --b;
		if(t == 'U') {
			cin >> c >> d >> e;
			--c, --d;
			update_x(a, b, e);
			update_x(c + 1, b, -e);
			update_x(a, d + 1, -e);
			update_x(c + 1, d + 1, e); 
		} else
			cout << query_x(0, a, 0, b) << '\n';
	}
	return 0;
}