#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int N = 1414214;
 
bitset<N> is_prime;
vector<int> prime_numbers;
 
void compute_primes() {
	is_prime.set();
	is_prime[1] = 0;
 
	for(int p = 2; p * p < N; ++p) {
		if(!is_prime[p])
			continue;
 
		for(int i = 2 * p; i < N; i += p)
			is_prime[i] = 0;
	}
 
	for(int i = 2; i < N; ++i) {
		if(is_prime[i])
			prime_numbers.push_back(i);
	}
}
 
bool check_prime(int64_t n) {
	if(n < N)
		return is_prime[n];
 
	for(int p : prime_numbers) {
		if(1ll * p * p > n)
			break;
		else if(n % p == 0)
			return false;
	}
 
	return true;
}
 
int64_t next_prime(int64_t n) {
	do
	{
		++n;
	} while (!check_prime(n));
	
	return n;
}
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	compute_primes();
 
	int t;
 
	cin >> t;
 
	while(t--) {
		int64_t n;
 
		cin >> n;
 
		cout << next_prime(n) << '\n';
	}
 
	return 0;
}