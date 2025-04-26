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
	int x, p, k;	
	Evento() {}
	Evento(int X, int Y, int Z) : x {X}, p {Y}, k {Z} {}
};
bool operator<(Evento e1, Evento e2) {
	return e1.x < e2.x || (e1.x == e2.x && e1.p < e2.p);
}
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	while(cin >> n) {

		vector<Evento> evento;
		int fotos = 0;

		vector<bool> usa(n, false);
		stack<int> p;

		evento.reserve(2 * n);

		for(int i = 0; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			evento.push_back(Evento(a, 0, i));
			evento.push_back(Evento(b, 1, i));
		}

		sort(evento.begin(), evento.end());

		for(Evento& e : evento) {
			if(e.p) {
				if(usa[e.k]) continue;
				fotos += p.size() > 0;
				while(!p.empty()) {
					usa[p.top()] = true;
					p.pop();
				}
			} else
				p.push(e.k);
		}
		cout << fotos << '\n';
	}
	return 0;
}