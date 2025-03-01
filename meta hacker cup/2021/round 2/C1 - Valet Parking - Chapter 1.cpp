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

const int inf = 1e9;

int r, c, k;
vector<string> g;

int count_moves() {
	vector<int> cnt(c, 0), lo(c, 0);
	
	int ans = INT_MAX, n = c;
	
	for(int i = 0; i < k - 1; ++i) {
		for(int j = 0; j < c; ++j) if(g[i][j] == 'X') ++cnt[j];
	}
	
	vector<vector<int>> S(c);
	
	for(int i = k - 1; i < r; ++i) {
		for(int j = 0; j < c; ++j) {
			if(g[i][j] == 'X')
				S[j].emplace_back(i);
		}
	}
	
	for(int j = 0; j < c; ++j) S[j].emplace_back(inf);
	
	for(int i = 0; i < r; ++i) {
		int L = 0;
		for(int j = 0; j < c; ++j) {
			
			if(cnt[j] < k && S[j][lo[j]] - i < k - 1) ++cnt[j], ++lo[j];
			
			if(cnt[j] == k || S[j][lo[j]] - i == k - 1) ++L;
		}
		
		ans = min(ans, i + L);
	}
	
	return ans;
}
 
void solve() {
	
	cin >> r >> c >> k;
	
	g.resize(r);
	for(string& s : g) cin >> s;
		
	int ans = count_moves();
	
	for(int j = 0; j < c; ++j)
		for(int i = 0; i < r / 2; ++i)
			swap(g[i][j], g[r - i - 1][j]);
	
	k = r - k + 1;
	cout << min(ans, count_moves()) << '\n';
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
