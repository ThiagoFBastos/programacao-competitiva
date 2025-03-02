#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <bitset>
#include <numeric>
#include <cmath>
#include <cstdlib>

using namespace std;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	
	cin >> t;
	
	for(int i = 1; i <= t; ++i) {
		
		int n, g;
		int dist = numeric_limits<int> :: max(), pos = -1;
		
		cin >> n >> g;
		
		vector<int> energy(n);
		
		for(int& e : energy)
			cin >> e;
		
		sort(energy.begin(), energy.end());
		
		for(int i = n - 1; i >= 0; --i) {
			if(dist > abs(g - energy[i])) {
				pos = n - i;
				dist = abs(g - energy[i]);
			}
		}
		
		cout << "Case #" << i << ": " << pos << ' ' << dist << '\n';
	}
}