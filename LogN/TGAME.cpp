#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

const int N = 1e5+5;
int n, x, y, par[N], deg[N];
int f[N];
vector<int> child[N];

int mex(int x) {
    vector<int> val;
    for (int i: child[x]) val.push_back(f[i]);
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < val.size(); ++i)
        if (val[i] != i) return i;
    return val.size();
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("TGAME.inp", "r", stdin);
    freopen("TGAME.out", "w", stdout);

    while (cin >> n >> x >> y) {
        if (n == 0) break;
        memset(deg, 0, sizeof deg);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; ++i) child[i].clear();
        
        for (int i = 1; i <= n; ++i) {
            cin >> par[i];
            child[par[i]].push_back(i);
            ++deg[par[i]];
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
            if (!deg[i])
                q.push(i);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (--deg[par[u]] == 0) {
                f[par[u]] = mex(par[u]);
                q.push(par[u]);
            }
        }

        int g = f[x] ^ f[y];
        if (g) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}