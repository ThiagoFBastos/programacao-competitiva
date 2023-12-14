#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 24 * 1e6, M = 1e6;
 
int nr = 1, roots[M+10], len[M+10], le[N], ri[N], cur;
char letter[N];
 
int build(int l, int r) {
	int p = cur++;
	if(l != r) {
		int m = (l + r) / 2;
		le[p] = build(l, m);
		ri[p] = build(m + 1, r);
	}
	return p;
}
 
int upd(int k, char c, int l, int r, int p) {
	int np = cur++;
	le[np] = le[p], ri[np] = ri[p];
	if(l == r) letter[np] = c;
	else {
		int m = (l + r) / 2;
		if(k <= m) le[np] = upd(k, c, l, m, le[p]);
		else ri[np] = upd(k, c, m + 1, r, ri[p]);
	}
	return np;
}
 
char query(int k, int l, int r, int p) {
	if(l == r) return letter[p];
	int m = (l + r) / 2;
	return k <= m ? query(k, l, m, le[p]) : query(k, m + 1, r, ri[p]);
}
 
void Init() {
	roots[0] = build(0, M - 1);
}
 
void TypeLetter(char L) {
	len[nr] = 1 + len[nr - 1];
	roots[nr] = upd(len[nr - 1], L, 0, M - 1, roots[nr - 1]);
	++nr;
}
 
void UndoCommands(int U) {
	len[nr] = len[nr - U - 1];
	roots[nr] = roots[nr - U - 1];
	++nr;
}
 
char GetLetter(int P) {
	return query(P, 0, M - 1, roots[nr - 1]); 
}
