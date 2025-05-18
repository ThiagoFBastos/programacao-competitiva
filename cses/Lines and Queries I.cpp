#include <bits/stdc++.h>
 
using namespace std;
 
class LiChao {
 
public:
 
	using Fx = pair<long long, long long>;
 
	LiChao(vector<int>& x): coords {x} {
		sort(coords.begin(), coords.end());
		coords.resize(unique(coords.begin(), coords.end()) - coords.begin());
		st.assign(4 * coords.size(), make_pair<int>(1e9, 1e9));
	}
 
	void add(Fx f) {
		add(f, 0, (int)coords.size() - 1);
	}
 
	auto query(int x) {
		return query(x, 0, (int)coords.size() - 1);
	}
 
private:
 
	long long eval(Fx f, int x) {
		return f.first * x + f.second;
	}
 
	void add(Fx f, int l, int r, int p = 1) {
		int m = (l + r) / 2;
 
		bool v1 = eval(f, coords[l]) < eval(st[p], coords[l]);
		bool v2 = eval(f, coords[m]) < eval(st[p], coords[m]);
 
		if(v2) swap(f, st[p]);
 
		if(l == r) return;
		else if(v1 != v2) add(f, l, m, 2 * p);
		else add(f, m + 1, r, 2 * p + 1); 
	}
 
	long long query(int x, int l, int r, int p = 1) {
		auto y = eval(st[p], x);
 
		if(l == r) return y;
 
		int m = (l + r) / 2;
 
		return min(y, x <= coords[m] ? query(x, l, m, 2 * p) : query(x, m + 1, r, 2 * p + 1));
	}
 
	vector<Fx> st;
	vector<int> coords;
};
 
int main() {
 
	ios_base::sync_with_stdio(false);
	cin.tie(0);
 
	using query = tuple<int, int, int>;
 
	int q;
	vector<int> coords;
 
	cin >> q;
 
	vector<query> queries(q);
 
	for(int i = 0; i < q; ++i) {
		int t;
 
		cin >> t;
 
		if(t == 1) {
			int a, b;
			cin >> a >> b;
			queries[i] = {1, a, b};
		} else {
			int x;
			cin >> x;
			queries[i] = {2, x, -1};
			coords.push_back(x);
		}
	}
 
	LiChao seg(coords);
 
	for(auto [type, a1, a2] : queries) {
		if(type == 1) {
			seg.add({-a1, -a2});
		} else
			cout << -seg.query(a1) << '\n';
	}
 
	return 0;
}
