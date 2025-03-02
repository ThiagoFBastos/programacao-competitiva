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

vector<long long> F1{1,2,3,4,5,6,7,8,9};

void f1(long long n, int d, int k) {
	if(k == 0) {
		F1.push_back(n);
		return;
	}
	
	if(k != 1)
		f1(10 * n + d, d, k - 1);
	
	for(; d < 9; ++d)
		f1(10 * n + d + 1, d + 1, k - 1);
}

long long a, b;
int m, ans;

void f2(long long n, int d, int k) {
	if(k == 0) {
		if(n >= a && n <= b && n % m == 0) ++ans;
		return;
	}
	
	f2(10 * n + d, d, k - 1);
	
	for(; d > 1; --d)
		f2(10 * n + d - 1, d - 1, k - 1);
}

int digits(long long n) {
	int ans = 0;
	for(; n; n /= 10) ++ans;
	return ans;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	
	for(int k = 1; k + 1 <= 9; ++k)
		for(int d = 1; d <= 9; ++d)
			f1(0, d, k + 1);
	
	sort(F1.begin(), F1.end());
	F1.resize(unique(F1.begin(), F1.end()) - F1.begin());
	
	int t;
	
	cin >> t;

	for(int i = 1; i <= t; ++i) {
		
		ans = 0;
		
		cin >> a >> b >> m;
		
		for(auto x : F1) {
			if(x >= 10) {
				f2(x, x % 10 - 1, digits(x) - 1); 
			} else {
				if(x >= a && x <= b && x % m == 0) ++ans;
			}
		}
		
		cout << "Case #" << i << ": " << ans << '\n';
	}
}