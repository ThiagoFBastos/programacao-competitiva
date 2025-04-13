#include "bits/stdc++.h"
#define endl '\n'

using namespace std;

using ii = pair<int, int>;

const int maxn = 2e3, inf = 1e9;

ii p[maxn];
bool inset[maxn];

int det(ii a, ii b, ii c) {
	return (b.first * c.second - b.second * c.first) - 
		    a.first * (c.second - b.second) + 
		    a.second * (c.first - b.first);
}

bool cw(ii a, ii b, ii c) {
	return det(a, b, c) <= 0;
}

bool ccw(ii a, ii b, ii c) {
	return det(a, b, c) >= 0;
}

void hull(bool inset[], ii p[], int n, function<bool(ii, ii, ii)> cmp) {
	stack<int> st;
	
	st.push(0);
	
	for(int i = 1; i < n; ++i) {
		while((int)size(st) >= 2) {
			int k = st.top(); st.pop();
			if(cmp(p[i], p[k], p[st.top()])) {
				st.push(k);
				break;
			}
		}
		st.push(i);
	}
	
	while(!st.empty()) {
		inset[st.top()] = true;
		st.pop();
	}
}

int convex_hull(ii p[], int n) {
	if(n == 0) return 0;
	else if(n < 3) return -inf;
	
	int k = 0;
	
	memset(inset, 0, n * sizeof(bool));
	hull(inset, p, n, cw);
	hull(inset, p, n, ccw);
	
	for(int i = 0; i < n; ++i) if(!inset[i]) p[k++] = p[i];
	
	return 1 + convex_hull(p, k);
}

void solve() {
	int n;
	
	cin >> n;
	
	if(!n) exit(0);
	
	for(int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		p[i] = {x, y};
	}
	
	sort(p, p + n);
	
	int cnt = convex_hull(p, n);
	
	if(cnt < 0 || cnt % 2 == 0) cout << "Do not take this onion to the lab!" << endl;
	else cout << "Take this onion to the lab!" << endl;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(1) solve();
	return 0;
}