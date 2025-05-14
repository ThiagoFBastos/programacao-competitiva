#include <bits/stdc++.h>
 
using namespace std;
 
void print(__int128 num) {
	string s;
	
	if(num == (__int128)0)
		s = "0";
 
	while(num > 0) {
		s += num % 10 + '0';
		num /= 10;
	}
 
	reverse(s.begin(), s.end());
 
	cout << s << '\n';
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	vector<int> x(n), y(n);
 
	for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
 
	auto sum_dist = [](vector<int>& coords) -> __int128 {
		__int128 ans {}, sum {};
 
		sort(coords.begin(), coords.end());
 
		for(int i = 0; i < (int)coords.size(); ++i) {
			ans += 1ll * i * coords[i] - sum;
			sum += coords[i];
		}
 
		return ans;
	};
 
	print(sum_dist(x) + sum_dist(y));
 
	return 0;
}