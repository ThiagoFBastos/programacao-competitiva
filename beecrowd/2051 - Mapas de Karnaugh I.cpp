#include <cstdio>

using namespace std;

int main() {

	short n, v[4];
	
	scanf("%hd", &n);

	for(int i = 0; i < n; ++i) {

		short **mapak {}, m, a, b, len, r {};

		scanf("%hd", &m);

		if(i)
			putchar('\n');

		len = 1 << m;
		a = len / m;
		b = len / a;

		mapak = new short*[a];

		for(int k = 0; k < a; ++k)
			mapak[k] = new short[b];

		for(int k = len; k; --k) {

			short l = 0, c = 0;
		
			for(int j = 0; j < m; ++j)
				scanf("%hd", &v[j]);

			for(int j = 0; j < m + 1 >> 1; ++j)
				c = (c << 1) + v[j];

			for(int j = m + 1 >> 1; j < m; ++j)
				l = (l << 1) + v[j];

			scanf(" - %hd", &mapak[l][c]);

			len -= mapak[l][c];
		}

		puts("Mapa de Karnaugh");

		if(m == 2)
			printf("  0 1\n0|%hd %hd\n1|%hd %hd\n", mapak[0][0], mapak[0][1], mapak[1][0], mapak[1][1]);

		else if(m == 3)
			printf("  00 01 11 10\n0|%hd  %hd  %hd  %hd\n1|%hd  %hd  %hd  %hd\n", mapak[0][0], mapak[0][1], mapak[0][3], mapak[0][2], mapak[1][0], mapak[1][1], mapak[1][3], mapak[1][2]);

		else {

			printf("   00 01 11 10\n00|%hd  %hd  %hd  %hd\n01|%hd  %hd  %hd  %hd\n", mapak[0][0], mapak[0][1], mapak[0][3], mapak[0][2], mapak[1][0], mapak[1][1], mapak[1][3], mapak[1][2]);
			printf("11|%hd  %hd  %hd  %hd\n10|%hd  %hd  %hd  %hd\n", mapak[3][0], mapak[3][1], mapak[3][3], mapak[3][2], mapak[2][0], mapak[2][1], mapak[2][3], mapak[2][2]);
		}

		if(!len)
			puts("Tautologia");

		else if(len == a * b)
			puts("Contradicao");

		else
			puts("Contingencia");
	}

	return 0;
}