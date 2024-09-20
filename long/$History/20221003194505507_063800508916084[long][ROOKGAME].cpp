#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

void solve() {
    int n, m, k; cin >> n >> m >> k;
    int g = 0;
    for (int i = 1; i <= k; ++i) {
        int x, y; cin >> x >> y;
        g ^= ((x-1) ^ (y-1)) + 1;
    }
    if (g) cout << "YES\n";
    else cout << "NO\n";
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("ROOKGAME.inp", "r", stdin);
    freopen("ROOKGAME.out", "w", stdout);

    for (int i = 0; i < 5; ++i)
        solve();
    return 0;
}