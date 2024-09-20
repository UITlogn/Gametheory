#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

const int N = 1e5+5;
int n, m, a[N];
int deg[N];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("GGAME.inp", "r", stdin);
    freopen("GGAME.out", "w", stdout);

    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        ++deg[u];
    }

    bool ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (deg[i]) ans ^= a[i] & 1;
    }
    cout << (ans ? "YES" : "NO");
    return 0;
}