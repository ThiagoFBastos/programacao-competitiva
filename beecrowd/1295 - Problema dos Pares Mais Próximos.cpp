#include "bits/stdc++.h"
using namespace std;

using pt = pair<double, double>;

void solve() {
  int n, k = 0;

  cin >> n;

  if(!n) exit(0);

  vector<pt> p(n);
  set<pt> S;
  double mindist = 1e9;

  for(int i = 0; i < n; ++i) {
    double x, y;
    cin >> x >> y;
    p[i] = {x, y};
  }

  sort(p.begin(), p.end());

  for(int i = 0; i < n; ++i) {

    swap(p[i].first, p[i].second);
 
    while(k < i && p[i].second - p[k].second >= mindist) S.erase(p[k++]);

    auto j = S.lower_bound({p[i].first - mindist, -1e9});
    double h = mindist;

    while(j != S.end() && abs(j->first - p[i].first) <= h) {
        mindist = min(mindist, hypot(j->first - p[i].first, j->second - p[i].second));
        ++j;
    }

     S.insert(p[i]);
  }

  if(mindist >= 1e4) cout << "INFINITY\n";
  else cout << mindist << '\n';
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
    cout.setf(ios_base :: fixed);
    cout.precision(4);
	int t = 1;
	//cin >> t;
	while(1) solve();
 	return 0;
}