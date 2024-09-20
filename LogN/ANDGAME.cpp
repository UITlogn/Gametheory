#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

#define MASK(i) (int)(1LL << (i))
#define SET1(msk, i) (int)((msk) | MASK(i))
#define SET0(msk, i) (int)((msk) & ~MASK(i))
#define BIT(msk, i) (int)(((msk) >> (i)) & 1ll)
#define cnt1(x) (int)__builtin_popcountll((int)(x))
#define cntl(x) (int)__builtin_clzll((int)(x))
#define cntr(x) (int)__builtin_ctzll((int)(x))

const int N = 66, M = 1e5+5, MOD = 1e9+7;
int n, a[M];

int Pow(int a, int b, int M = MOD) {
    a %= M;
    if (b == 0) return 1;
    if (b == 1) return a %M;
    int t = 1;
    while (b) {
        if (b & 1) t = t*a %M;
        a = a*a %M;
        b >>= 1;
    }
    return t;
}

int f[N], g[N];
int C(int k, int n) {
    return f[n] * g[k] % MOD * g[n-k] % MOD;
}
void prepare() {
    f[0] = g[0] = 1;
    for (int i = 1; i < N; ++i)
        f[i] = f[i-1] * i % MOD;
    g[N-1] = Pow(f[N-1], MOD-2, MOD);
    for (int i = N-2; i > 0; --i)
        g[i] = g[i+1] * (i+1) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("ANDGAME.inp", "r", stdin);
    freopen("ANDGAME.out", "w", stdout);

    prepare();
    cin >> n;
    int g = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] = cnt1(a[i]);
        g ^= a[i];
    }
    
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int f = g ^ a[i];
        if (f < a[i]) {
            ans += C(f, a[i]) * Pow(2, 63 - a[i], MOD) % MOD;
            ans %= MOD;
        }
    }
    cout << ans;
    return 0;
}