#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

bool can_place(i64 x, i64 y, i64 a, i64 b, i64 c) {
	x -= (a + y - 1) / y;
	if(x <= 0) return false;
	i64 z = (b + x - 1) / x + (c + x - 1) / x;
	return z <= y;
}

void solve() {

	i64 x, y, a, b, c;
	
	cin >> x >> y >> a >> b >> c;
	
	i64 z = (a + x - 1) / x + (b + x - 1) / x + (c + x - 1) / x;
	
	if(z <= y) {
		cout << "Yes\n";
		return;
	}
	
	z = (a + y - 1) / y + (b + y - 1) / y + (c + y - 1) / y;
	
	if(z <= x) {
		cout << "Yes\n";
		return;
	}
	
	bool flag = false;
	
	for(int k = 0; k < 2; ++k) {
		for(int i = 0; i < 3; ++i) {
			if(i==0)flag=flag||can_place(x,y,a,b,c);
			if(i==1)flag=flag||can_place(x,y,b,a,c);
			if(i==2)flag=flag||can_place(x,y,c,b,a);
		}
		swap(x, y);
	}
	
	cout << (flag ? "Yes\n" : "No\n");
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
//	cin >> t;
	while(t--) solve();
 	return 0;
}
