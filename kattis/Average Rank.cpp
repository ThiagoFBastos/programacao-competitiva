#include "bits/stdc++.h"

using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i32 = int;
using u32 = unsigned;
using i16 = short;
using u16 = unsigned short;
using ld = long double;
using ii = pair<int, int>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<class T>
struct BIT {
    vector<T> bit;
    
    BIT() {}
    
    BIT(int n) {
        bit.assign(n + 1, 0);
    }
    
    void upd(int k, T x) {
        for(++k; k < int(bit.size()); k += k & -k) bit[k] += x;
    }
    
    T query(int k) {
        T ans {};
        for(++k; k > 0; k -= k & -k) ans += bit[k];
        return ans;
    }
    
    T query(int l, int r) {
        if(l > r) return (T)0;
        return query(r) - query(l - 1);
    }
};

template<class T>
struct BITRange {
    BIT<T> X, Y;
    
    BITRange(int n) {
        X = BIT<T>(n);
        Y = BIT<T>(n);
    }
    
    void upd(int l, int r, T x) {
        X.upd(l, (l - 1) * x);
        X.upd(r + 1, -r * x);
        Y.upd(l, x);
        Y.upd(r + 1, -x);
    }
    
    T prefix(int k) {
        return k * Y.query(k) - X.query(k);
    }
    
    T query(int l, int r) {
        return prefix(r) - prefix(l - 1);
    }
};

void solve() {
    
    int n, w;
    
    cin >> n >> w;
    
    BITRange<i64> bit(w + 1);
    vector<int> pontos(n, 0), last(n, 0);
    vector<tuple<int, int, int, int>> evento;
    vector<i64> media(n, 0);
    
    for(int i = 1; i <= w; ++i) {
        int m;
        cin >> m;
        while(m--) {
            int id;
            cin >> id;
            --id;
            if(i - 1) evento.emplace_back(pontos[id], max(1, last[id]), i - 1, id); 
            last[id] = i;
            ++pontos[id];
        }
    }
    
    for(int i = 0; i < n; ++i) evento.emplace_back(pontos[i], max(1, last[i]), w, i);
    
    sort(evento.rbegin(), evento.rend());
    
    for(int i = 0; i < (int)evento.size(); ) {
        int j, p = get<0>(evento[i]);
        for(j = i; j < (int)evento.size(); ++j) {
            auto [_, l, r, id] = evento[j];
            if(_ != p) break;
            media[id] += r - l + 1 + bit.query(l, r);
        }
        for(; i < j; ++i) {
            auto [_, l, r, id] = evento[i];
            bit.upd(l, r, 1);
        }
    }
    
    cout.precision(8);
    cout.setf(ios_base :: fixed);
    
    for(i64 x : media) cout << x / (double)w << '\n';
}
 
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
//  cin >> t;
    while(t--) solve();
    return 0;
}