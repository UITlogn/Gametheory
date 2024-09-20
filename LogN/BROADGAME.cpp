#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

int gcd(int a, int b) {
    while (b != 0) swap(b, a %= b); 
    return a; 
}
struct fract {
    int x, y;
    fract() {
        x = 0; y = 1;
    }
    fract(int a, int b) {
        int g = gcd(a, b);
        x = a/g; y = b/g;
    }
    bool operator < (fract a) {
        return (x * a.y > a.x * y);
    }
};

int calc(int n, int m) {
    vector<fract> val;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            val.push_back(fract(i, j));
    sort(val.begin(), val.end());

    for (int i = 0; i < val.size()-1; ++i) {
        if (!(val[i] < val[i+1])) {
            return i;
        }
    }
    return val.size();
}
bool solve() {
    int n; cin >> n;
    int g = 0;
    while (n--) {
        int x, y; cin >> x >> y;
        g ^= calc(x, y);
    }
    return g > 0;
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("BROADGAME.inp", "r", stdin);
    freopen("BROADGAME.out", "w", stdout);

    for (int i = 1; i <= 3; ++i) {
        cout << (solve() ? "YES" : "NO") << '\n';
    }
    return 0;
}