#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long
#define II pair<int,int>
#define fi first
#define se second
const int N = 1e3+5;
int n, m;
int a[N][N];
int pre[N][N];
bool f[N][N];
bool col[N][3], row[N][3];

int get(int x, int y, int u, int v) {
    return pre[u][v] - pre[u][y-1] - pre[x-1][v] + pre[x-1][y-1];
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            pre[i][j] = a[i][j] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
        }

    memset(f, 0, sizeof f);
    memset(col, 0, sizeof col);
    memset(row, 0, sizeof row);
    for (int j = 0; j <= m; ++j) col[j][0] = 1;
    for (int i = 0; i <= n; ++i) row[i][0] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            int k = pre[i][j] % 3;
            if (col[j][(k + 2) % 3]) {
                f[i][j] = 1;
            }
            if (row[i][(k + 2) % 3]) {
                f[i][j] = 1;
            }
            col[j][k] |= !f[i][j];
            row[i][k] |= !f[i][j];
        }
    cout << f[n][m] << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("FGAME.inp", "r", stdin);
    freopen("FGAME.out", "w", stdout);

    for (int i = 0; i < 5; ++i) {
        solve();
    }
    return 0;
}