#include "shoes.h"
 
using namespace std;
 
template<class T>
struct BIT {
	vector<T> bit;
	
	BIT(int n) {
		bit.assign(n + 1, 0);
	}
	
	void upd(int k, T x) {
		for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
	}
	
	T query(int k) {
		T ans {};
		for(++k; k > 0; k -= k & -k) ans += bit[k];
		return ans;
	}
	
	T query(int l, int r) {
		if(l > r) return (T)0;
		return query(r) - query(l - 1);
	}
};
 
long long count_swaps(vector<int> s) {
	int n = s.size(), id = 0;
	
	vector<vector<int>> pos(n + 1), neg(n + 1);
	vector<int> loPos(n + 1, 0), loNeg(n + 1, 0);
	vector<bool> marked(n, false);
	
	for(int i = 0; i < n; ++i) {
		if(s[i] < 0) neg[-s[i]].push_back(i);
		else pos[s[i]].push_back(i);
	}
	
	for(int i = 0; i < n; ++i) {
		if(marked[i]) continue;
		if(s[i] < 0) {
			int k = pos[-s[i]][loPos[-s[i]]++];
			++loNeg[-s[i]];
			s[k] = id + 1;
			s[i] = id;
			marked[k] = true;
		} else {
			int k = neg[s[i]][loNeg[s[i]]++];
			++loPos[s[i]];
			s[k] = id;	
			s[i] = id + 1;
			marked[k] = true;
		}
		id += 2;
	}
	
	BIT<long long> bit(n);
	auto ans = 0LL;
	
	for(int v : s) {
		ans += bit.query(v + 1, n - 1);
		bit.upd(v, 1);
	}
 
	return ans;
}
