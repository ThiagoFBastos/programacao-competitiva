#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 30;
 
vector<int> gauss[N];
 
int msb(int x) {
	if(!x) return 0;
	return 31 - __builtin_clz(x);
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n, k {};
	
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		int x;
 
		cin >> x;
 
		if(x) 
			gauss[msb(x)].push_back(x);
	}
 
	for(int i = N - 1; i >= 0; --i) {
		auto& S = gauss[i];
 
		if(S.empty())
			continue;
 
		++k;
 
		int pivot = S[0];
 
		for(int x : S) {
			int y = x ^ pivot;
 
			if(y)
				gauss[msb(y)].push_back(y);
		}
	}
 
	cout << (1ll << k) << '\n';
 
	return 0;
}
