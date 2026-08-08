#include "bits/stdc++.h"
using namespace std;
struct LinkedList {
	int rank, cnt;
	long long sum;
	LinkedList* next;
	LinkedList(int v) : cnt {1}, rank {}, sum {v + 1}, next {} {}
};
struct DSU {
	vector<LinkedList*> pai;
	LinkedList* find_set(LinkedList* v) {
		return v->next ? v->next = find_set(v->next) : v;
	}
	void join(int u, int v) {
		auto U = find_set(pai[u]);
		auto V = find_set(pai[v]);
		if(U == V) return;
		else if(U->rank < V->rank) {
			U->next = V;
			V->sum += U->sum;
			V->cnt += U->cnt;
		} else {
			V->next = U;
			U->sum += V->sum;
			U->cnt += V->cnt;
			U->rank += U->rank == V->rank;
		}
	}
	void push(int u, int v) {
		auto new_no = new LinkedList(u);
		pai.push_back(pai[u]);
		auto past_no = find_set(pai[u]);
		auto no = find_set(pai[v]);
		--past_no->cnt, past_no->sum -= u + 1;
		no->sum += u + 1, ++no->cnt, no->rank += !no->rank, new_no->next = no;
		pai[u] = new_no;
	}
	DSU(int n) {
		pai.resize(n);
		for(int v = 0; v < n; ++v) pai[v] = new LinkedList(v);
	}
	~DSU() {
		for(auto x : pai) delete x;
	}
};
void solve() {
	int n, m;
	while(cin >> n >> m) {
		DSU dsu(n);
		while(m--) {
			int t, x, y;
			cin >> t >> x;
			if(t == 1) {
				cin >> y;
				dsu.join(x - 1, y - 1);
			} else if(t == 2) {
				cin >> y;
				dsu.push(x - 1, y - 1);
			} else {
				auto S = dsu.find_set(dsu.pai[x - 1]);
				cout << S->cnt << ' ' << S->sum << '\n';
			}
		}
	}
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}