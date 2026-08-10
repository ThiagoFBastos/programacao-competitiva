#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;

int main() {

	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	string s, t;

	cin >> s >> t;

	int cs[26], ct[26], h[26];

	memset(h, 0, sizeof h);
	memset(cs, 0, sizeof cs);
	memset(ct, 0, sizeof ct);

	for(int k = 0; k < s.size(); ++k) {

		++h[s[k] - 'A'];
		++ct[t[k] - 'A'];
		++cs[s[k] - 'A'];
	}

	int op = 0;

	deque<char> C;

	for(int k = 0; k < 26; ++k) {

		if(ct[k] > cs[k]) {

			op += ct[k] - cs[k];

			for(int i = ct[k] - cs[k]; i > 0; --i)
				C.push_back(k + 'A');
		}
	}

	sort(C.begin(), C.end());	

	for(int k = 0; k < s.size(); ++k) {

		char c = s[k] - 'A';

		if(cs[c] > ct[c] && (C.front() < c + 'A' || cs[c] - ct[c] == h[c])) {

			--cs[c];
			++cs[C.front() - 'A'];

			s[k] = C.front();
			C.pop_front();
		}

		--h[c];
	}

	cout << op << '\n';
	cout << s << '\n';

	return 0;
}