class Solution {
    void solve(vector<int>& a, int l, int r) {
        if(l == r) return;
        int n = r - l + 1, k = 0;
        vector<int> tmp(n);
        for(int i = l; i <= r; i += 2) tmp[k++] = a[i];
        for(int i = l + 1; i <= r; i += 2) tmp[k++] = a[i];
        for(int i = 0; i < n; ++i) a[i + l] = tmp[i];
        solve(a, l, l + (n - 1) / 2);
        solve(a, l + (n - 1) / 2 + 1, r);
    }
public:
    vector<int> beautifulArray(int n) {
        vector<int> p(n);
        for(int i = 0; i < n; ++i) p[i] = i + 1;
        solve(p, 0, n - 1);
        return p;
    }
};