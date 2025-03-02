#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <algorithm>
#include <bitset>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdio>
#include <random>
#include <chrono>
#include <climits>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	
	cin >> t;
	
	for(int i = 1; i <= t; ++i) {
		int n;
		
		cin >> n;
		
		long double l = 0, r = INT_MAX;
		
		for(int j = 1; j <= n; ++j) {
			int a, b;
			cin >> a >> b;
			long double lo = 1.0L * j / b, hi = a ? 1.0L * j / a : INT_MAX;
			
			if(max(l, lo) <= min(r, hi)) {
				l = max(l, lo);
				r = min(r, hi);
			} else {
				l = 0;
				r = -1;
			}
		}
		
		cout << "Case #" << i << ": ";
		cout.precision(9);
		cout.setf(ios_base::fixed);
		
		if(l <= r) cout << l << '\n';
		else cout << "-1\n";
	}
}