#include "horses.h"
#include <utility>
#include <vector>
#include <cmath>
#include <algorithm>
 
const int mod = 1e9 + 7;
 
using value = std :: pair<double, int>;
using i64 = long long;
 
std :: vector<value> maxlg;
std :: vector<double> lg;
std :: vector<int> prod, X, Y;
int N;
 
value op(value a, double b, int c) {
	a.first += b;
	a.second = (i64)a.second * c % mod;
	return a;
}
 
void load(int lo, int hi, int no = 1) {
	if(lo == hi) {
		maxlg[no] = std :: make_pair(log(X[lo]) + log(Y[lo]), (i64)X[lo] * Y[lo] % mod);
		lg[no] = log(X[lo]);
		prod[no] = X[lo];
	} else {
		int mid = (lo + hi) / 2;
		load(lo, mid, 2 * no);
		load(mid + 1, hi, 2 * no + 1);
		lg[no] = lg[2 * no] + lg[2 * no + 1];
		maxlg[no] = std :: max(maxlg[2 * no], op(maxlg[2 * no + 1], lg[2 * no], prod[2 * no]));
		prod[no] = (i64)prod[2 * no] * prod[2 * no + 1] % mod;
	}
}
 
void upd(int k, int x, int y, int lo, int hi, int no = 1) {
	if(lo == hi) {
		X[lo] = x, Y[lo] = y;
		maxlg[no] = std :: make_pair(log(X[lo]) + log(Y[lo]), (i64)X[lo] * Y[lo] % mod);
		lg[no] = log(X[lo]);
		prod[no] = X[lo];	
	} else {
		int mid = (lo + hi) / 2;
		if(k <= mid) upd(k, x, y, lo, mid, 2 * no);
		else upd(k, x, y, mid + 1, hi, 2 * no + 1);
		lg[no] = lg[2 * no] + lg[2 * no + 1];
		maxlg[no] = std :: max(maxlg[2 * no], op(maxlg[2 * no + 1], lg[2 * no], prod[2 * no]));
		prod[no] = (i64)prod[2 * no] * prod[2 * no + 1] % mod;		 
	}
}
 
int init(int N, int X[], int Y[]) {
	int lg = 31 - __builtin_clz(N);
	maxlg.resize(4 << lg);
	prod.resize(4 << lg);
	:: lg.resize(4 << lg);
	:: X.resize(N);
	:: Y.resize(N);
	:: N = N;
	for(int i = 0; i < N; ++i) :: X[i] = X[i], :: Y[i] = Y[i];
	load(0, N - 1);
	return maxlg[1].second;
}
 
int updateX(int pos, int val) {
	upd(pos, val, Y[pos], 0, N - 1);
	return maxlg[1].second;
}
 
int updateY(int pos, int val) {
	upd(pos, X[pos], val, 0, N - 1);
	return maxlg[1].second;
}
