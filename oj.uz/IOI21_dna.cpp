#include "dna.h"
 
using namespace std;
 
const int N = 1e5 + 100;
 
int cnt[N][3][3];
 
void transform(string& s) {
	for(char& ch : s) {
		if(ch == 'A') ch = '0';
		else if(ch == 'T') ch = '1';
		else ch = '2';
	}
}
 
void init(string a, string b) {
	transform(a);
	transform(b);
	int n = a.size();
	for(int i = 1; i <= n; ++i) {
		for(int k = 0; k < 3; ++k)
		for(int j = 0; j < 3; ++j)
			cnt[i][k][j] = cnt[i - 1][k][j];
		++cnt[i][a[i - 1] - '0'][b[i - 1] - '0'];
	}
}
 
int get_distance(int x, int y) {
	
	int f[3][3] = {{0}}, X[3] = {0}, Y[3] = {0}, pairs = 0, triples = 0;
	
	++x, ++y;
 
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			f[i][j] += cnt[y][i][j] - cnt[x - 1][i][j];
			X[i] += cnt[y][i][j] - cnt[x - 1][i][j];
			Y[j] += cnt[y][i][j] - cnt[x - 1][i][j];
		}
	}
 
	for(int i = 0; i < 3; ++i) {
		if(X[i] != Y[i])
			return -1;
	}
 
	for(int i = 0; i < 3; ++i) {
		for(int j = i + 1; j < 3; ++j) {
			int X = min(f[i][j], f[j][i]);
			f[i][j] -= X;
			f[j][i] -= X;
			pairs += X;
		}
	}
 
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			if(i == j) continue;
			triples += f[i][j];
		}
	}
 
	return pairs + 2 * triples / 3;
}
