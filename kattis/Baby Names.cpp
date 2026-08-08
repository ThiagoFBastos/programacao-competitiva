#include "bits/stdc++.h"

using namespace std;

const int N = 2e5 * 30 + 1;

using ii = pair<int, int>;

int t[N][26], cnt[N][2], nos = 1;

void push(string& s, int g) {
	int i = 0;
	for(char ch : s) {
		if(t[i][ch - 'A'] == -1) {
			memset(t[nos], -1, sizeof t[nos]);
			t[i][ch - 'A'] = nos++;
		}
		++cnt[i][g];
		i = t[i][ch - 'A'];
	}
	++cnt[i][g];
}

void remove(string& s, int g) {
	int i = 0;
	for(char ch : s) {
		--cnt[i][g];
		i = t[i][ch - 'A'];
	}
	--cnt[i][g];
}

int count(string& s, int g = -1) {
	int T = 0, i = 0;
	for(char ch : s) {
		if(i < 0) break;
		for(int j = 0; j < ch - 'A'; ++j) {
			int no = t[i][j];
			if(no < 0) continue;
			if(g < 0) T += cnt[no][0] + cnt[no][1];
			else T += cnt[no][g];
		}
		i = t[i][ch - 'A'];
	}
	return T;
}

void solve() {

	memset(t[0], -1, sizeof t[0]);
	
	map<string, int> genero;
	
	while(true) {
		int type, gen;
		string name1, name2;
		
		cin >> type;
		
		if(!type) return;
		
		switch(type) {
			case 1:
				cin >> name1 >> gen;
				genero[name1] = gen - 1;
				push(name1, gen - 1);
				break;
			case 2:
				cin >> name1;
				gen = genero[name1];
				remove(name1, gen);
				break;
			case 3:
				cin >> name1 >> name2 >> gen;
				cout << count(name2, gen - 1) - count(name1, gen - 1) << '\n';
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	int t = 1;
	//cin >> t;
	while(t--) solve();
 	return 0;
}