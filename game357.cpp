#include <bits/stdc++.h>
using namespace std;
#define int long long

int dp[4][6][8];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("ab.inp", "r", stdin);
    freopen("ab.out", "w", stdout);

    dp[0][0][0] = 0; // i^j^k = 0: thua
    for (int i = 0; i <= 3; ++i)
        for (int j = 0; j <= 5; ++j)
            for (int k = 0; k <= 7; ++k) {
                if (!dp[i][j][k]) {
                    for (int x = i + 1; x <= 3; ++x)
                        dp[x][j][k] = 1;
                    for (int x = j + 1; x <= 5; ++x)
                        dp[i][x][k] = 1;
                    for (int x = k + 1; x <= 7; ++x)
                        dp[i][j][x] = 1;
                }
            }
    for (int i = 3; i >= 0; --i)
        for (int j = 5; j >= 0; --j)
            for (int k = 7; k >= 0; --k) {
                cout << i << ' ' << j << ' ' << k;
                // dp[i][j][k] << '\n';
                // cout << ' ' << (i ^ j ^ k);
                cout << " -> ";
                if (dp[i][j][k]) while (1) {
                    bool flag = 0;
                    for (int x = i - 1; x >= 0; --x)
                        if (!dp[x][j][k]) {
                            cout << x << ' ' << j << ' ' << k;
                            flag = 1;
                            break;
                        }
                    if (flag) break;
                    for (int x = j - 1; x >= 0; --x)
                        if (!dp[i][x][k]) {
                            cout << i << ' ' << x << ' ' << k;
                            flag = 1;
                            break;
                        }
                    if (flag) break;
                    for (int x = k - 1; x >= 0; --x)
                        if (!dp[i][j][x]) {
                            cout << i << ' ' << j << ' ' << x;
                            break;
                        }
                    break;
                }
                cout << '\n';
            }

    return 0;
}