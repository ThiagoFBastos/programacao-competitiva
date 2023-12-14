#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, h[MAXN], L[MAXN];
	long long max_area = 0;
	deque<int> H;
	cin >> n;
	for(int k = 0; k < n; ++k) {
		cin >> h[k];
		while(!H.empty() && h[H.back()] >= h[k]) H.pop_back();
		if(H.empty()) L[k] = 0;
		else L[k] = H.back();
		H.push_back(k);
	}
	while(!H.empty()) H.pop_back();
	for(int k = n - 1; k >= 0; --k) {
		while(!H.empty() && h[H.back()] >= h[k]) H.pop_back();
		int r;
		if(H.empty()) r = n - 1;
		else r = H.back();
		H.push_back(k);
		if(h[r] < h[k]) --r;
		if(h[L[k]] < h[k]) ++L[k];
		max_area = max(max_area, h[k] * (r - L[k] + 1LL));
	}
	cout << max_area << '\n';
	return 0;
}
