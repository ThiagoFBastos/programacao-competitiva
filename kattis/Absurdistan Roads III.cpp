#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree <T, null_type ,  less<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

template<class T>
using ordered_multiset = tree <T, null_type ,  less_equal<T> ,  rb_tree_tag ,  tree_order_statistics_node_update>;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

const int maxn = 1e5;

int n, prim[2][maxn], R[maxn];
vii G[2][maxn];
ii pai[2][maxn], e[2 * maxn];
bool emp[2 * maxn], livre[2][maxn];

void matching();

void matching() {
    fill(livre[0], livre[0] + n, true);
    fill(livre[1], livre[1] + n, true);
    bool run;
    do
    {
        queue<ii> S;
        run = false;
        for(int k = 0; k < n; ++k) {
            pai[0][k] = make_pair(-1, -1);
            if(livre[0][k]) {
                pai[0][k].first = -2;
                prim[0][k] = k;
                S.push({k, 0});
            }
        }
        fill(pai[1], pai[1] + n, make_pair(-1, -1));
        while(!S.empty()) {
            auto [a, b] = S.front();
            S.pop();
            if(b && livre[1][a] && livre[0][prim[1][a]]) {
                run = true;
                livre[1][a] = livre[0][prim[1][a]] = false;
                for(int u = a, t = 1; ; t ^= 1) {
                    auto [v, epos] = pai[t][u];
                    if(v < 0) break;
                    emp[epos] = t;
                    u = v;
                }
            }
            for(auto [u, epos] : G[b][a]) {
                if(emp[epos] == b && pai[b ^ 1][u].first == -1) {
                    pai[b ^ 1][u] = make_pair(a, epos);
                    prim[b ^ 1][u] = prim[b][a];
                    S.push({u, b ^ 1});
                }
            }
        }
    } while(run);
    for(int k = 0; k < 2 * n; ++k)
        if(emp[k]) R[e[k].first - 1] = e[k].second; 
}
int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        e[2 * i] = make_pair(a, b);
        e[2 * i + 1] = make_pair(b, a);
        --a, --b;
        G[0][a].push_back({i, 2 * i});
        G[1][i].push_back({a, 2 * i});
        G[0][b].push_back({i, 2 * i + 1});
        G[1][i].push_back({b, 2 * i + 1});
    }
    matching();
    for(int k = 0; k < n; ++k) 
        cout << k + 1 << ' ' << R[k] << '\n';
    return 0;
}