#include <bits/stdc++.h>

using namespace std;

int main() {
	
	int palitos[10001];
	int digitos[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
	int testes;
	
	for(int k = 0; k <= 10000; ++k)
		palitos[k] = 0;
		
	for(int k = 1; k < 10; ++k)
		++palitos[digitos[k]];
		
	for(int k = 2; k <= 10000; ++k) {
		
		for(int i = 0; i <= 9; ++i) {
		
			if(k > digitos[i])
				palitos[k] = (palitos[k] + palitos[k - digitos[i]]) % 1000007;
		}
	}
	
	scanf("%d", &testes);
	
	while(testes--) {
	
		int quantidade;
		
		scanf("%d", &quantidade);
		
		if(quantidade == 6)
			printf("%d\n", 1 + palitos[quantidade]);
			
		else
			printf("%d\n", palitos[quantidade]);
	}
	
	return 0;
}