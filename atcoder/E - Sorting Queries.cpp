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

void solve() {
	int q;

	cin >> q;

	queue<int> unord;
	multiset<int> ord;

	while(q--) {
		int t, x;
		cin >> t;
		if(t == 1) {
			cin >> x;
			unord.push(x);
		} else if(t == 2) {
			if(!ord.empty()) {
				cout << *ord.begin() << '\n';
				ord.erase(ord.begin());
			} else {
				cout << unord.front() << '\n';
				unord.pop();
			}
		} else {
			while(!unord.empty()) {
				ord.insert(unord.front());
				unord.pop();
			}
		}
	}
}	

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}
