#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	const int MAXN = 2e5;
	int n, t[MAXN], low = -1, high;
	long long t1 = 0, t2 = 0;
	cin >> n;
	high = n;
	for(int i = 0; i < n; ++i)
		cin >> t[i];
	sort(t, t + n);
	while(low < high - 1) {
		if(t1 <= t2) t1 += t[++low];
		else t2 += t[--high];
	}
	int l = 0, r = n - 1;
	if(t1 <= t2) {
		while(r > high) 
			t1 += t[r--];
		t1 = max(t1, t2) + t[high];
		while(l < high) t2 += t[l++];
	}
	else {
		while(l < low) 
			t2 += t[l++];
		t2 = max(t2, t1) + t[low];
		while(r > low) t1 += t[r--];
	}
	cout << max(t1, t2) << '\n';
	return 0;
}
