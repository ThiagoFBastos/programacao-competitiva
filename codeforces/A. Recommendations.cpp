#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;


int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;

	cin >> n;

	vii p(n);

	for(int k = 0; k < n; ++k) cin >> p[k].first;
	for(int k = 0; k < n; ++k) cin >> p[k].second;

	sort(p.begin(), p.end());

	map<ii, int> S;
	int k = p[0].first;
	ll t = 0;

	S[make_pair(p[0].second, p[0].first)] = 1;

	for(int i = 1; i < n; ++i) {

		if(p[i].first != k) {

			while(!S.empty() && k < p[i].first) {

				auto it = prev(S.end());

				ii c = it->first;

				t += 1LL * (k - c.second) * c.first;

				if(--it->second == 0)
					S.erase(it);

				++k;
			}

			k = p[i].first;
		}

		++S[make_pair(p[i].second, p[i].first)];
	}

	while(!S.empty()) {

		auto it = prev(S.end());

		ii c = it->first;

		t += 1LL * (k - c.second) * c.first;

		if(--it->second == 0)
			S.erase(it);

		++k;
	}

	cout << t << '\n';
	
	return 0;
}
