#include "bits/stdc++.h"
using namespace std;
int mod_sum(int a, int b) {
    return a >= b ? a - b : a;
}
auto suffix_array(string& s) {
    s += "#";
    int n = size(s);
    vector<int> pos[2], val[2], cnt(max(127, n) + 1, 0);
    for(int i = 0; i < 2; ++i) {
        pos[i].resize(n);
        val[i].resize(n);
    }
    for(char c : s) ++cnt[c + 1];
    for(int i = 1; i < 127; ++i) cnt[i] += cnt[i - 1];
    for(int i = 0; i < n; ++i) pos[0][cnt[s[i]]++] = i;
    val[0][pos[0][0]] = 0;
    for(int i = 1; i < n; ++i) val[0][pos[0][i]] = val[0][pos[0][i - 1]] + (s[pos[0][i]] != s[pos[0][i - 1]]);
    for(int k = 0; (1 << k) < n; ++k) {
        fill(cnt.begin(), cnt.end(), 0);
        for(int i = 0; i < n; ++i) ++cnt[val[0][i] + 1];
        for(int i = 1; i < n; ++i) cnt[i] += cnt[i - 1];
        for(int i = 0; i < n; ++i) {
            int j = mod_sum(pos[0][i] - (1 << k) + n, n);
            pos[1][cnt[val[0][j]]++] = j;
        }
        val[1][pos[1][0]] = 0;
        for(int i = 1; i < n; ++i) {
            int x = pos[1][i - 1], y = pos[1][i];
            auto a = make_pair(val[0][x], val[0][mod_sum(x + (1 << k), n)]);
            auto b = make_pair(val[0][y], val[0][mod_sum(y + (1 << k), n)]);
            val[1][y] = val[1][x] + (a != b);
        }
        for(int i = 0; i < n; ++i) {
            pos[0][i] = pos[1][i];
            val[0][i] = val[1][i];
        }
    }
    s.pop_back();
    pos[0].erase(pos[0].begin());
    return pos[0];
}
struct SegTree {
    struct Node {
        int cnt;
        Node *left, *right;
    };  
    vector<Node*> st;
    Node *create(int lo, int hi) {
        Node *no = new Node;
        no->cnt = 0;
        if(lo != hi) {
            int mid = (lo + hi) / 2;
            no->left = create(lo, mid);
            no->right = create(mid + 1, hi);
        }
        return no;
    }
    Node *upd(Node* root, int k, int lo, int hi) {
        Node *no = new Node;
        if(lo == hi) no->cnt = 1 + root->cnt;   
        else {
            int mid = (lo + hi) / 2;
            if(k <= mid) {
                no->left = upd(root->left, k, lo, mid);
                no->right = root->right;
            } else {
                no->left = root->left;
                no->right = upd(root->right, k, mid + 1, hi);
            }
            no->cnt = no->left->cnt + no->right->cnt;
        }
        return no;
    }
    int query(Node* L, Node* R, int k, int lo, int hi) {
        if(lo == hi) return lo;
        int mid = (lo + hi) / 2;
        auto LL = L->left, RL = R->left;
        if(RL->cnt - LL->cnt >= k) return query(LL, RL, k, lo, mid);
        return query(L->right, R->right, k - RL->cnt + LL->cnt, mid + 1, hi);
    }
    SegTree(vector<int>& a) {   
        int n = size(a);
        st.resize(n + 1);
        st[0] = create(0, n - 1);
        for(int i = 1; i <= n; ++i) st[i] = upd(st[i - 1], a[i - 1], 0, n - 1);
    }
    int kesimo(int l, int r, int k) {
        return query(st[l], st[r + 1], k, 0, int(st.size()) - 2);
    }
};
void solve() {
    string s;
    int q, n;
    cin >> s;
    n  = size(s);
    auto sufixo = suffix_array(s);
    SegTree st(sufixo);
    cin >> q;
    s += "A";
    while(q--) {
        string t;
        int k;
        cin >> t >> k;
        int L = 0, R = n - 1;
        for(int i = 0; i < int(size(t)); ++i) {
            int l = L, r = R;
            for(int j = 31 - __builtin_clz(R - L + 1); j >= 0; --j) {
                if(l + (1 << j) <= R && s[min(n, sufixo[l + (1 << j)] + i)] < t[i]) l += 1 << j;
                if(r - (1 << j) >= L && s[min(n, sufixo[r - (1 << j)] + i)] > t[i]) r -= 1 << j;
            }
            if(s[min(n, sufixo[l] + i)] != t[i]) ++l;
            if(s[min(n, sufixo[r] + i)] != t[i]) --r;
            L = l, R = r;
            if(l > r) break;
        }
        if(R - L + 1 < k) cout << "-1\n";
        else cout << 1 + st.kesimo(L, R, k) << '\n';
    }
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}