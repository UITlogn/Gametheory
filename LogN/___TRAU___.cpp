#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

bool maxi(int &a, int x) {
    if (a < x) return a = x, 1;
    else return 0;
}
bool mini(int &a, int x) {
    if (a > x) return a = x, 1;
    else return 0;
}
const int N = 805, M = N*2;
int n, a[N];
int pre[N];

int dp[N][N]; // max khi đi i thao tác đầu, dừng tại j

void check(int m) {
    int pos = 0;
    for (int i = 1; i <= n; ++i)
}
void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }

    int l = 0, r = N, ans;
    while (l <= r) {
        int mid = l + r >> 1;
        if (check(mid)) {
            ans = mid;
            r = mid-1;
        } else
            l = mid+1;
    }
    cout << ans;
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("DRILL.inp", "r", stdin);
    freopen("DRILL.out", "w", stdout);

    int t; cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}