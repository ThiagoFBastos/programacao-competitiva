#include "bits/stdc++.h"

using namespace std;

auto manacher(vector<int>& s) {
	int l = 0, r = -1, len = 0, n = s.size();
	vector<int> d1(n, 1), d2(n, 0);
	
	for(int i = 0; i < n; ++i) {
		
		if(i <= r) {
			d1[i] = min(d1[l + r - i], r - i + 1);
			d2[i] = min(d2[l + r - i + 1], r - i + 1);
		}
		
		while(i + d1[i] < n && i - d1[i] >= 0 && s[i - d1[i]] == s[i + d1[i]]) ++d1[i];
		
		while(i + d2[i] < n && i - d2[i] - 1 >= 0 && s[i - d2[i] - 1] == s[i + d2[i]]) ++d2[i];
		
		if(r < i + d2[i] - 1) l = i - d2[i], r = i + d2[i] - 1;
		if(r < i + d1[i] - 1) l = i - d1[i] + 1, r = i + d1[i] - 1;
		
		if(r == n - 1) len = max(len, r - l + 1);
	}
	
	return d2;
}	

void solve(int test) {
    int n;

    cin >> n;

    vector<int> a(4 * n), sum_nless(4 * n + 1, 0), sum_ngreater(4 * n + 1, 0);

    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> a[i + n];
    for(int i = 2 * n; i < 4 * n; ++i) a[i] = a[i - 2 * n];

    for(int i = n; i < 4 * n; ++i) {
        sum_nless[i + 1] = sum_nless[i] + (a[i - n] >= a[i]);
        sum_ngreater[i + 1] = sum_ngreater[i] + (a[i - n] <= a[i]);
    }

    auto pal = manacher(a);
    int ans = INT_MAX;

    for(int i = n; i <= 3 * n; ++i) {
        int mid = (n + 2) / 2;

        int SL = sum_nless[mid + i - 1] - sum_nless[i];
        int SG = sum_ngreater[i + n] - sum_ngreater[i + mid];

        if(!SL && !SG && pal[i] >= n)
            ans = min(ans, i - n);
    }

    if(ans == INT_MAX) ans = -1;

    cout << "Case #" << test << ": " << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);

    int t = 1;

    cin >> t;

    for(int i = 1; i <= t; ++i) solve(i);

    return 0;
}

