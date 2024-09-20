#include <bits/stdc++.h>                                                                                                                   //Vu Hoang Long
using namespace std;
#define int long long

const int N = 1e5+5;
int n, a[N], f[N];

int mex(vector<int> &val) {
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    for (int i = 0; i < val.size(); ++i)
        if (val[i] != i) return i;
    return val.size();
}
void prepare() {
    f[0] = 0;
    for (int i = 1; i <= 1e3+5; ++i) {
        vector<int> val;
        for (int j = 1; j <= (i+1)/2; ++j)
            val.push_back(f[i-j]);
        f[i] = mex(val);
        bitset<10> b = i;
        bitset<10> c = f[i];
        cout << b << ' ' << c << '\n';
    }
}
/*
1111...1111 -> 1000...0000  (xóa n-1 bit nhỏ nhất) (f[i] = (i+1)/2)
1000...0000 -> 0010...0000  (bit 1 đầu lùi 2)
1000...0001 -> 0100...0001  (bit 1 đầu lùi 1)

i lẻ: f[i] = (i+1)/2
i chẵn: f[i] = (i >> k) xóa 2 bit 0 nhỏ nhất
*/
int calc(int i) {
    if (i & 1) return i + 1 >> 1;
    int cnt = 0;
    while (1) {
        if ((i & 1) == 0) ++cnt;
        i >>= 1;
        if (cnt == 2) break;
    }
    return i;
}
void solve() {
    int g = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        // g ^= f[a[i]];
        g ^= calc(a[i]);
    }
    cout << (g ? "yes" : "no");
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("HALFGAME.inp", "r", stdin);
    freopen("HALFGAME.out", "w", stdout);

    // prepare();
    while (cin >> n) {
        solve();
        cout << '\n';
    }
    return 0;
}