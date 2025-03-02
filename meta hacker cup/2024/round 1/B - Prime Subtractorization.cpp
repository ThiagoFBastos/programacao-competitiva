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

const int N = 1e7 + 10;

bitset<N> isPrime;
int two[N];

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(nullptr);
	
	isPrime.set();
	
	for(int i = 2; i * i < N; ++i)
		for(int j = 2 * i; j < N; j += i)
			isPrime[j] = 0;
		
	for(int k = 5; k < N; ++k)
		two[k] = two[k - 1] + (isPrime[k] && isPrime[k - 2]);
	
	int t;
	
	cin >> t;
	
	for(int i = 1; i <= t; ++i) {
		int n;
		cin >> n;
		cout << "Case #" << i << ": ";
		if(n >= 5)
			cout << two[n] + 1 << '\n';
		else
			cout << "0\n";
	}
}