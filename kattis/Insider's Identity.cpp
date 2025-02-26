#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using ld = long double;
using ii = pair<int, int>;

const int K = 2;

struct Vertex {
    int next[K];
    int go[K];
    int par;
    int link;
    bool leaf;
    char ch;
    
    Vertex(int p, char ch = '$') : par {p}, ch {ch} {
        link = 0;
        leaf = false;
        memset(next, -1, sizeof next);
        memset(go, -1, sizeof go);
    }
};

struct Aho {
    vector<Vertex> st;

    Aho(vector<string>& words) {
        st.push_back(Vertex(0));
        for(auto& s : words) push(s);
        bfs();
    }

    void push(string& s) {
        int no = 0;
        for(char ch : s) {
            ch -= '0';
            if(st[no].next[ch] == -1) {
                st[no].next[ch] = st.size();
                st.emplace_back(no, ch);
            }       
            no = st[no].next[ch];
        }
        st[no].leaf = true;
    }

    void bfs() {
        queue<int> q;

        q.push(0);
        for(int i = 0; i < K; ++i) st[0].next[i] = max(0, st[0].next[i]);

        while(!q.empty()) {
            int from = q.front();
            q.pop();
            
            Vertex& no = st[from];
            char e = no.ch;
            int par = no.par;

            if(par) {   
                for(int v = st[no.par].link; v >= 0; v = st[v].link) {
                    Vertex& n = st[v];
                    if(n.next[e] != -1) {
                        no.link = n.next[e];
                        break;
                    }
                }
            }

            for(int i = 0; i < K; ++i) {
                int next = no.next[i];
                if(next <= 0) continue;
                q.push(next);
            }
        }
    }

    int go(int no, char ch) {
        Vertex& v = st[no];
        if(v.go[ch] != -1) return v.go[ch];
        return v.go[ch] = v.next[ch] != -1 ? v.next[ch] : go(v.link, ch);
    }

    int countNode() {
        return st.size();
    }
};

const int N = 1e6;

vector<i64> dp[2];

void solve() {
    int n, m;
    string pat;

    cin >> n >> pat;

    m = size(pat);

    vector<int> star;

    for(int i = 0; i < m; ++i) {
        if(pat[i] != '*') continue;
        star.push_back(i);
    }

    int q = size(star);

    if(n == m) {
        cout << (1 << q) << '\n';       
        return;
    }

    vector<string> words;

    for(int i = 0; i < (1 << q); ++i) {
        string p = pat;
        for(int k : star) p[k] = '0';
        for(int k = i; k; k -= k & -k) p[star[__builtin_ctz(k)]] = '1';
        words.push_back(p);
    }

    Aho aho(words);
    int nodes = aho.countNode();

    for(int i = 0; i < 2; ++i) dp[i].resize(nodes);
    
    fill(begin(dp[0]), end(dp[0]), 0);

    dp[0][0] = 1;

    for(int i = 0; i < n; ++i) {
        fill(begin(dp[1]), end(dp[1]), 0);

        for(int k = 0; k < nodes; ++k) {
            if(aho.st[k].leaf) continue;
            for(int ch : {0, 1}) {
                int j = aho.go(k, ch);
                if(aho.st[j].leaf) continue;
                dp[1][j] += dp[0][k];
            }
        }

        swap(dp[0], dp[1]);
    }

    cout << (1ll << n) - accumulate(begin(dp[0]), end(dp[0]), 0ll) << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}