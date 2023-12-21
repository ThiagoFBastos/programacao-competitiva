#include <bits/stdc++.h>
using namespace std;
struct I {
	int a, t, k;
};
bool operator<(I i1, I i2) {
	return i1.a < i2.a || (i1.a == i2.a && i1.t > i2.t);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	vector<I> m;
	vector<int> movie(n);
	for(int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		movie[i] = b;
		m.push_back({a, 0, i});
		m.push_back({b, 1, i});
	}
	sort(m.begin(), m.end());
	int films = 0;
	set<pair<int, int>> S;
	for(int i = 0; i < m.size(); ++i) {
		auto [c, t, j] = m[i];
		if(t == 0) {
			if(k) {
				++films;
				S.insert({movie[j], j});
				--k;
			}
			else if(S.rbegin()->first > movie[j]) {
				S.erase(prev(S.end()));
				S.insert({movie[j], j});
			}
		}
		else if(S.count({c, j})){
			++k;
			S.erase({c, j});
		}
	}
	cout << films << '\n';
	return 0;
}
