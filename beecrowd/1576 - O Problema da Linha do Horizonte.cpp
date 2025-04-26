#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

struct Evento {
	int x, h, fim;
	Evento() {}
	Evento(int a, int b, int c) : x {a}, h {b}, fim {c} {}
};
bool operator<(Evento e1, Evento e2) {
	return e1.x < e2.x || (e1.x == e2.x && e1.fim < e2.fim || (e1.x == e2.x && e1.fim == e2.fim && e1.h > e2.h));
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int l, r, h;
	vector<Evento> e;
	vii p;
	multiset<int> S;
	while(cin >> l >> h >> r) {
		e.push_back(Evento(l, h, 0));
		e.push_back(Evento(r, h, 1));
	}
	sort(e.begin(), e.end());
	for(int k = 0; k < (int)e.size(); ) {
		int i = k;
		if(e[k].fim == 0) {
			if(S.empty() || *S.rbegin() < e[k].h) 
				p.push_back({e[k].x, e[k].h});
			for(; i < (int)e.size() && e[i].x == e[k].x && !e[i].fim; ++i)
				S.insert(e[i].h);
		} else {
			for(; i < (int)e.size() && e[i].x == e[k].x && e[i].fim; ++i)
				S.erase(S.find(e[i].h));
			if(S.empty())
				p.push_back({e[k].x, 0});
			else if(*S.rbegin() < e[k].h)
				p.push_back({e[k].x, *S.rbegin()});
		}
		k = i;
	}
	for(int i = 0; i < (int)p.size() - 1; ++i)
		cout << p[i].first << ' ' << p[i].second << ' ';
	cout << p.back().first << ' ' << p.back().second << '\n';
	return 0;
}