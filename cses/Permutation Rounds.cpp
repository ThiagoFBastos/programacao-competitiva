#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 2e5 + 5, MOD = 1e9 + 7;
 
vector<int> cycles(vector<int>& p) {
	int n = p.size();
	vector<bool> visited(n, false);
	vector<int> sizes;
 
	for(int v = 0; v < n; ++v) {
		if(visited[v]) continue;
		int i {};
		
		do
		{
			++i;
			visited[v] = true;
			v = p[v];
		} while (!visited[v]);
		
		sizes.push_back(i);
	}
 
	return sizes;
}
 
bitset<N> has_value, is_prime;
 
int lcm(vector<int>& a) {
	int maxn {}, ans = 1;
 
	for(int x : a) {
		has_value[x] = 1;
		maxn = max(maxn, x);
	}
 
	is_prime.set();
 
	for(int p = 2; p <= maxn; ++p) {
		if(!is_prime[p]) continue;
 
		int max_power {};
 
		for(int i = p; i <= maxn; i += p) {
			is_prime[i] = 0;
			
			if(!has_value[i])
				continue;
 
			int power {};
 
			for(int k = i; k % p == 0; k /= p)
				++power;
 
			max_power = max(max_power, power);
		}
 
		for(int i = 0; i < max_power; ++i)
			ans = 1LL * ans * p % MOD;
	}
 
	return ans;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	int n;
 
	cin >> n;
 
	vector<int> p(n);
 
	for(int& v : p) { cin >> v; --v; }
 
	auto sizes = cycles(p);
 
	cout << lcm(sizes) << '\n';
 
	return 0;
}
