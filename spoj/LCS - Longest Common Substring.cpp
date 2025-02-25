#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <tuple>
#include <stack>
#include <utility>

using namespace std;

vector<int> suffix_array(string& s);
vector<int> suffix_array(string& s) {
    int n = s.size();
    vector<int> p(n), pt(n), c(n), ct(n), cnt(1 + max(128, n), 0);
    for(char ch : s) ++cnt[ch + 1];
    for(int k = 1; k < 128; ++k) cnt[k] += cnt[k - 1];
    for(int k = 0; k < n; ++k) c[k] = cnt[s[k]];
    for(int k = 0; k < n; ++k) p[cnt[s[k]]++] = k;
    int lv = 31 - __builtin_clz(n);
    for(int i = 0; i <= lv; ++i) {
        fill(cnt.begin(), cnt.end(), 0);
        for(int k = 0; k < n; ++k) {
            int j = p[k] - (1 << i);
            if(j < 0) j += n;
            ++cnt[c[j] + 1];
        }
        for(int k = 1; k < n; ++k) cnt[k] += cnt[k - 1];
        for(int k = 0; k < n; ++k) {
            int j = p[k] - (1 << i);
            if(j < 0) j += n;
            pt[cnt[c[j]]++] = j;
        }
        copy(pt.begin(), pt.end(), p.begin());
        ct[p[0]] = 0;
        for(int k = 1; k < n; ++k) {
            int u = p[k], v = p[k] + (1 << i), w = p[k - 1], x = p[k - 1] + (1 << i);
            if(v >= n) v -= n;
            if(x >= n) x -= n;
            ct[p[k]] = (c[u] != c[w] || c[v] != c[x]) + ct[p[k - 1]];
        }
        copy(ct.begin(), ct.end(), c.begin());
    }
    return p;
}

int main() {
    ios_base :: sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    string a, b, c;
    cin >> a >> b;
    c = a + '#' + b + '$';
    vector<int> s = suffix_array(c);
    int n = s.size(), lp = 0;
    vector<int> p(n), pos(n);
    vector<vector<int>> cnt(2);
    vector<pair<int, int>> I(n);
    stack<pair<int, int>> S;
    for(int k = 0; k < 2; ++k) cnt[k].resize(n + 1);
    for(int k = 0; k < n; ++k) pos[s[k]] = k;
    cnt[0][0] = cnt[1][0] = 0;
    for(int k = 0; k < n; ++k) {
        if(s[k] < (int)a.size()) cnt[0][k + 1] = 1;
        else cnt[1][k + 1] = 1;
        cnt[0][k + 1] += cnt[0][k];
        cnt[1][k + 1] += cnt[1][k];
        if(pos[k] == 0) 
            p[pos[k]] = 0;
        else {
            int j = s[pos[k] - 1];
            int i = lp;
            while(i + max(k, j) < n && c[i + k] == c[i + j]) ++i;
            p[pos[k]] = i;
            lp = max(0, i - 1);
        }
    }
    for(int k = 0; k < n; ++k) {
        while(!S.empty() && S.top().first >= p[k]) S.pop();
        I[k].first = S.empty() ? k - 1 : S.top().second;
        S.push({p[k], k});
    }
    while(!S.empty()) S.pop();
    for(int k = n - 1; k >= 0; --k) {
        while(!S.empty() && S.top().first >= p[k]) S.pop();
        I[k].second = S.empty() ? k : S.top().second - 1;
        S.push({p[k], k});
    }
    int ans = 0;
    for(int k = 0; k < n; ++k) {
        if(p[k]) {
            int l = I[k].first, r = I[k].second;
            if(cnt[1][r + 1] - cnt[1][l] && cnt[0][r + 1] - cnt[0][l])
                ans = max(ans, p[k]);
        }
    }
    cout << ans << '\n';
    return 0;
}