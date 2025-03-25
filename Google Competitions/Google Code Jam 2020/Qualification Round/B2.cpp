#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
using namespace std;
#define f first
#define s second
#define EPS 1e-9
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned ui;
using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;
using vii = vector<ii>;
int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	for(int i = 1; i <= t; ++i) {
	    string s, ans;
	    int p = 0;
	    cin >> s;
	    for(char ch : s) {
	        if(p < ch - '0') {
	           while(p < ch - '0') {
	                ++p;
	                ans.push_back('(');
	           }
	        }
	        else if(p > ch - '0') {
	            while(p > ch - '0') {
	                --p;
	                ans.push_back(')');
	            }
	        }
	        ans.push_back(ch);
	    }
	    while(p) {
	        --p;
	        ans.push_back(')');
	    }
	    cout << "Case #" << i << ": " << ans << '\n';
	}
	return 0;
}