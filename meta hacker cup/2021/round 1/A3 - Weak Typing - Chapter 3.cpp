#include "bits/stdc++.h"

using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve() {
	string u;
	int k;
	ll n = 0, m = 0, pa = 0, ans = 0, X = 0, Y = 0, first[2] = {-1, -1}, last[2] = {-1, -1};
	char first_type = '.', last_type = '.';
	
	cin >> k >> u;
	
	for(char ch : u) {
		if(ch == '.') m <<= 1;
		else ++m;
		m %= mod;
	}
	
	for(char ch : u) {
		if(ch == 'F') ++n;
		else if(ch == 'O') {
			if(last_type == 'X') {
				ans = (ans + (last[1] + 1) * (m - n)) % mod;
				X = (X + last[1] + 1) % mod;
				Y = (Y + m - n) % mod;
				++pa;
			}
			if(first_type == '.') first_type = ch, first[0] = n;
			last[0] = n++;
			last_type = ch;
		} else if(ch == 'X') {
			if(last_type == 'O') {
				ans = (ans + (last[0] + 1) * (m - n)) % mod;
				X = (X + last[0] + 1) % mod;
				Y = (Y + m - n) % mod;
				++pa;
			}
			if(first_type == '.') first_type = ch, first[1] = n;
			last[1] = n++;
			last_type = ch;
		} else {
			ans = (2 * ans + n * (Y - X - n * pa % mod)) % mod;
			X = (2 * X + n * pa) % mod;
			Y = (2 * Y - n * pa) % mod;
			pa <<= 1;
			if(last_type == 'X' && first_type == 'O') {
				++pa;
				ans = (ans + (last[1] + 1) * (m - first[0] - n)) % mod;
				X = (X + last[1] + 1) % mod;
				Y = (Y + m - first[0] - n) % mod;
			} else if(last_type == 'O' && first_type == 'X') {
				++pa;
				ans = (ans + (last[0] + 1) * (m - first[1] - n)) % mod;
				X = (X + last[0] + 1) % mod;
				Y = (Y + m - first[1] - n) % mod;
			}
			if(last[0] != -1) last[0] = (last[0] + n) % mod;
			if(last[1] != -1) last[1] = (last[1] + n) % mod;
			n <<= 1;
		}	
		n %= mod;
		pa %= mod;
	}
	
	cout << (ans + mod) % mod << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}
 	return 0;
}
