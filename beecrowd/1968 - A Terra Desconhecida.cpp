#include <cstdio>
#include <cmath>

#define MOD 1000000007

using namespace std;

int *primeNumbers = NULL;
size_t length = 1;

int modulo(int, int);
int smallestFactor(int);

int main() {

	int *factors = nullptr;

	int a, b, n, k, p = 0;

	scanf("%d%d%d", &a, &b, &n);

	if(n == 1 && a <= 1 && b >= 1) {

		puts("1");
		return 0;
	}

	else if(n == 1) {

		puts("0");
		return 0;
	}

	primeNumbers = new int[664579];

	primeNumbers[0] = 3;

	factors = new int[b];

	factors[0] = 1;
	factors[1] = factors[2] = 2;

	if(n == 2 && a <= 2 && b >= 2) ++p;
	if(n == 2 && a <= 3 && b >= 3) ++p;

	for(k = 4; k < a; ++k) {

		int factor, count = 0;
		long long power = 1;

		factor = smallestFactor(k);

		L1:
		

			power *= factor;
			++count;

		if(!(k % power))
			goto L1;

		power /= factor;

		factors[k - 1] = count * factors[k / power - 1];
	}

	for(; k <= b; ++k) {

		int factor, count = 0;
		long long power = 1;

		factor = smallestFactor(k);

		L2:
		

			power *= factor;
			++count;

		if(!(k % power))
			goto L2;

		power /= factor;

		factors[k - 1] = count * factors[k / power - 1];

		if(factors[k - 1] == n) ++p;
	}

	k = b - a + 1 - p;

	printf("%d\n", modulo(p, k));
	
	return 0;
}

int modulo(int n, int p) {

	long long mod = 1, power = n;

	while(p) {

		if(p & 1)
			mod = mod * power % MOD;

		p >>= 1;
		power = power * power % MOD;
	}

	return mod;
}

int smallestFactor(int n) {

	if(!(n & 1))
		return 2;

	int L = sqrt(n);

	for(int k = 0; primeNumbers[k] <= L; ++k) {

		if(!(n % primeNumbers[k]))
			return primeNumbers[k];
	}

	primeNumbers[length++] = n;

	return n;
}