#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

const int N = 1e5+5;
bool dp[N];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("GAME3579.inp", "r", stdin);
    freopen("GAME3579.out", "w", stdout);

    dp[0] = dp[1] = dp[2];

    for (int i = 3; i < N; ++i) {
        for (int j: {3, 5, 7, 9}) {
            if (!dp[i-j]) {
                dp[i] = 1;
            }
        }
    }
    // for (int i = 1; i < N; ++i)
    //     if (!dp[i])
    //         cout << i << '\n';

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n % 12 < 3) cout << 2 << '\n';
        else cout << 1 << '\n';
    }
    return 0;
}