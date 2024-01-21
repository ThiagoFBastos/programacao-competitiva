#include <bits/stdc++.h>

using namespace std;

void solve(int test) {
    string s;
    int k;
    cin >> s >> k;
   
    vector<vector<char>> mod(k);

    for(int i = 0; i < (int)s.size(); ++i) mod[i % k].push_back(s[i]);
    
    for(auto& M : mod) sort(M.begin(), M.end());

    for(int i = 0; i < k; ++i) {    
        int j = i;
        for(char c : mod[i]) {
           s[j] = c;
           j += k;
        }
    }

    cout << s << '\n';
}

int main() {
    int t = 1;
    //cin >> t;
    for(int i = 1; i <= t; ++i) solve(i);
    return 0;
}

