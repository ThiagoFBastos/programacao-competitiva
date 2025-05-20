#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 5e3, M = 672, MOD = 1e9 + 7;
 
vector<int> getPrimes(int n) {
	vector<int> primes;
 
	auto is_prime = [](int x) -> bool {
		if(x <= 1) return false;
		else if(x <= 3) return true;
		else if(x % 2 == 0) return false;
 
		for(int i = 3; i * i <= x; i += 2)
			if(x % i == 0)
				return false;
 
		return true;
	};
 
	for(int i = 2; i <= n; ++i) {
		if(is_prime(i))
			primes.push_back(i);
	}
 
	return primes;
}
 
bitset<M> getSubsetMask(int n, vector<int>& primes) {
	bitset<M> S;
 
	for(int k = 0; k < (int)primes.size(); ++k) {
		int i = 0, p = primes[k];
 
		while(n % p == 0) {
			n /= p;
			i ^= 1;
		}
 
		S[k] = i;
	}
 
	return S;
}
 
int count_zero_xors(vector<bitset<M>>& a) {
	vector<bitset<M>> base(M);
 
	for(auto& S : a) {
		for(int i = M - 1; i >= 0; --i) {
			if(!S[i])
				continue;
 
			auto X = base[i] & S;
 
			if(X[i])
				S ^= base[i];
			else if(!base[i][i] && S[i]) {
				base[i] = S;
				break;
			}
		}
	}
 
	int zeroes = (int)a.size() - count_if(a.begin(), a.end(), [](auto& S) { return S.any();});
	int ans = 1;
 
	for(int i = 0; i < zeroes; ++i) {
		ans <<= 1;
		if(ans >= MOD)
			ans -= MOD;
	}
 
	return ans;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	auto primes = getPrimes(N);
	
	int n;
 
	cin >> n;
 
	vector<bitset<M>> a(n);
 
	for(int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		a[i] = getSubsetMask(x, primes);		
	}
 
	cout << count_zero_xors(a) << '\n';
 
	return 0;
}
