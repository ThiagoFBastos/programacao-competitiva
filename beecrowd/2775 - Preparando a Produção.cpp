#include <cstdio>

using namespace std;

#define MAX 1000

void read(int& n) {

	register int ch = getchar();

	n = 0;

	while(ch >= 0 && ch < 47)
		ch = getchar();

	while(ch > 47) {

		n = (n << 1) + (n << 3) + ch - 48;
		ch = getchar();
	}
}

int main(void) {

	int pacotes[MAX], tempo[MAX];
	int n;

	while(true) {

		int k, duracao = 0;

		read(n);

		if(feof(stdin))
			break;

		for(int k = 0; k < n; k++)
			read(pacotes[k]);

		for(int k = 0; k < n; k++)
			read(tempo[k]);

		for(int k = 1; k < n; k++){

			int val = pacotes[k], t = tempo[k], j;

			for(j = k - 1; j >= 0 && val < pacotes[j]; --j) {

				duracao += tempo[j] + t;
				pacotes[j + 1] = pacotes[j];
				tempo[j + 1] =	tempo[j];
			}

			pacotes[j + 1] = val;
			tempo[j + 1] = t;
		}

		printf("%d\n", duracao);
	}

	return 0;
}
