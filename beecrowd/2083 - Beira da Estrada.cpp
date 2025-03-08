#pragma GCC optimize("O3")

#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

template<class T>
int sig(T x) {
	return x >= 0 ? 1 : -1;
}

long long cross(ii a, ii b) {
	return 1LL * a.first * b.second - 1LL * a.second * b.first;
}

bool cmp(ii a, ii b) {
	if(sig(a.first) != sig(b.first)) return sig(a.first) > sig(b.first);
	return cross(a, b) > 0;
}

using LL = pair<long long, long long>;

auto find_pos(ii a, ii b) {
	b.first += a.first, b.second += a.second;
	if(a.first == b.first) return make_pair(a.first + 0LL, 1LL);
	long long A = b.second - a.second, B = b.first - a.first, C;
	C = b.second * B - A * b.first;
	return make_pair(-C, A);
}

struct compare {
	bool operator()(LL a, LL b) {
		return a.first * b.second < a.second * b.first;
	}
};

void solve() {
	int n;
	
	cin >> n;
	
	vector<ii> p(n), a(n);
	map<LL, int, compare> cnt;
	set<int> S;
	
	for(int i = 0; i < n; ++i) cin >> p[i].first >> p[i].second;
	
	for(int i = 0; i < n; ++i) {
		int m = 0;
		
		for(int j = 0; j < n; ++j) {
			if(p[i].second < p[j].second) {
				a[m++] = {p[j].first - p[i].first, p[j].second - p[i].second};
			}
		}
		
		if(!m) continue;
		
		sort(a.begin(), a.begin() + m, cmp);
		
		for(int j = 1; j < m; ++j) {
			if(cross(a[j - 1], a[j]) != 0)
				++cnt[find_pos(p[i], a[j - 1])];
		}
		
		++cnt[find_pos(p[i], a[m - 1])];
	}
	
	for(auto& x : cnt) S.insert(x.second);
	
	cout << 1 + S.size() << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
	return 0;
}