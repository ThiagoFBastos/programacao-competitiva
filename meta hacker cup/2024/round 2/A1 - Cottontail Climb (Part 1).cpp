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
	
	vector<long long> nums;
	
	for(int k = 0; 2 * k + 1 <= 18; ++k) {
		for(int d = 1; d <= 9; ++d) {
			if(d + k <= 9) {
				string s;
				for(int i = 0; i <= k; ++i)
					s += char(d + '0' + i);
				for(int i = 1; i <= k; ++i)
					s += char(d + k - i + '0');
				nums.push_back(stoll(s));
			}
		}
	}
	
	sort(nums.begin(), nums.end());
	
	for(int i = 1; i <= t; ++i) {
		long long a, b;
		int m, ans = 0;
		
		cin >> a >> b >> m;
		
		for(auto x : nums) {
			if(x < a || x > b) continue;
			ans += x % m == 0;
		}
		
		cout << "Case #" << i << ": " << ans << '\n'; 
	}
}