#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k;
	map<int, int> frequency;
 
	cin >> n >> k;
 
	vector<int> values(n);
 
	for(int& v : values)
		cin >> v;
 
	for(int i = 0; i < n; ++i) {
		if(i >= k) {
			auto it = frequency.find(values[i - k]);
			if(--it->second == 0)
				frequency.erase(it);
		}
 
		++frequency[values[i]];
 
		if(i >= k - 1)
			cout << frequency.size() << ' ';
	}
 
	cout << '\n';
 
	return 0;
}
