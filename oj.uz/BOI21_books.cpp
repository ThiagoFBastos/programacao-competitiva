#include <bits/stdc++.h>
 
#include "books.h"
 
using namespace std;
 
#define INF 1000000000
#define INFLL 1000000000000000000ll
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define fi first
#define sc second
 
using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;
 
//
// --- Sample implementation for the task books ---
//
// To compile this program with the sample grader, place:
//     books.h books_sample.cpp sample_grader.cpp
// in a single folder and run:
//     g++ books_sample.cpp sample_grader.cpp
// in this folder.
//
 
void solve(int N, int K, long long A, int S) {
 
	vector<i64> book(K);
	vector<int> pos(K);
 
	for(int i = 0; i < K; ++i) {
		book[i] = skim(i + 1);
		pos[i] = i + 1;
	}
 
	i64 sum = accumulate(all(book), 0ll);
 
	if(sum >= A && sum <= 2 * A) answer(pos);
	else if(sum > 2 * A) impossible();
 
	int l = 0, r = N;
 
	while(l < r) {
		int m = (l + r) / 2;
		if(skim(m + 1) > 2 * A - sum + book.back()) r = m;
		else l = m + 1;
	}
 
	if(--r >= 0 && skim(r + 1) >= A) {
		pos.back() = r + 1;
		answer(pos);
	}
	
	for(int i = 0; i < K && r >= K && sum < A; ++i, --r) {
		sum += skim(r + 1) - book[i];
		pos[i] = r + 1;
	}
	
	if(sum < A) impossible();
 
 	answer(pos);
}
