#include <bits/stdc++.h>
 
using namespace std;
 
#define MAXN 1000
 
int main() {
 
	int n, q;
 
	scanf("%d%d", &n, &q);
 
	int **preffix = new int*[n];
	char line[MAXN + 1];
 
	for(int k = 0; k < n; ++k) {
 
		preffix[k] = new int[n];
		scanf("%s", line);
 
		for(int j = 0; j < n; ++j) {
 
			int x = line[j] == '*';
 
			if(k && j)
				preffix[k][j] = x + preffix[k - 1][j] + preffix[k][j - 1] - preffix[k - 1][j - 1];
 
			else if(k)
				preffix[k][j] = x + preffix[k - 1][j];
 
			else if(j)
				preffix[k][j] = x + preffix[k][j - 1];
 
			else
				preffix[k][j] = x;
		}
	}
	
	while(q--) {
 
		int y1, x1, y2, x2;
 
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
 
		--x1, --x2, --y1, --y2;
 
		int r = preffix[y2][x2];
 
		if(x1 && y1)
			r = r - preffix[y2][x1 - 1] - preffix[y1 - 1][x2] + preffix[y1 - 1][x1 - 1];
 
		else if(x1)
			r = r - preffix[y2][x1 - 1];
 
		else if(y1)
			r -= preffix[y1 - 1][x2];
		
		printf("%d\n", r);
	}
 
	return 0;
}
