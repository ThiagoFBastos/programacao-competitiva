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
 
	int n, d, m;
 
	cin >> n >> d >> m;
 
	vector<ii> job(m);
 
	for(int i = 0; i < m; ++i) {
		cin >> job[i].first;
		job[i].second = i + 1;
	}
 
	sort(job.begin(), job.end());
 
	int lo = 1, hi = m;
 
	while(lo < hi) {
		int mid = (lo + hi) / 2, j = 0;
		bool ok = true;
		for(int i = 1; i <= n && j < m; ++i) {
			int k = j;
			while(k < m && k - j < mid && job[k].first <= i) {
				ok = ok && i - job[k].first <= d;
				++k;
			}
			j = k;
		}
		if(ok && j == m) hi = mid;
		else lo = mid + 1;
	}
 
	cout << hi << '\n';
 
	vector<vector<int>> sch(n + 1);
 
	for(int i = 1, j = 0; i <= n; ++i) {
		int k = j;
		while(k < m && k - j < hi && job[k].first <= i) sch[i].push_back(job[k++].second);
		j = k;
	}
 
	for(int i = 1; i <= n; ++i) {
		for(int id : sch[i]) cout << id << ' ';
		cout << "0\n";
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
