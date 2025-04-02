#include "bits/stdc++.h"

using namespace std;

using pt = pair<double, double>;

auto getPos(vector<int>& x) {
    int n = x.size();

    vector<double> X(n);
    vector<int> ptr(n);
    
    for(int i = 0; i < n; ++i) {
        X[i] = x[i];
        ptr[i] = i;
    }
    
    for(int i = 1; i < n; ++i) {
        if(X[i] > X[i - 1]) continue;
        
        double z = X[i];
        int k, m = 1;
        
        for(k = i - 1; k >= 0; k = ptr[k] - 1) {
            if(z / m > X[k]) break;
            m += k - ptr[k] + 1;    
            z += (k - ptr[k] + 1) * X[k];   
        }
        
        ptr[i] = k + 1;
        X[i] = z / m;
    }
    
    for(int i = n - 1; i >= 0; i = ptr[i] - 1)
        for(int j = ptr[i]; j <= i; ++j) 
            X[j] = X[i];

    return X;
}

void solve() {
    
    int n;
    
    cin >> n;
    
    vector<int> x(n), y(n);
    double ans = 0;
    
    for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
        
    auto X = getPos(x);
    auto Y = getPos(y);
    
    for(int i = 0; i < n; ++i) ans += pow(X[i] - x[i], 2) + pow(Y[i] - y[i], 2);
    
    cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--) solve();
    return 0;
}