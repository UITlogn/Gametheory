#include <bits/stdc++.h>                                                                                                                                                                                                                                                                                           //Created by CUBERLONG
using namespace std;                                                                                                                                                                                                                                                                                               //Created by CUBERLONG
#define int long long
void _time() {
    #ifndef ONLINE_JUDGE
        cout << "_\nTime : " << (int)clock() << "ms.\n";                                                                                                                                                                                                                                                                                           //Created by CUBERLONG
    #endif
}
void fast() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("ab.inp", "r", stdin);
        freopen("ab.out", "w", stdout);
    #endif
}
#define II pair<int,int>
#define fi first
#define se second

int n, m;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

II dxy[] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
string hxy = "v><^";

const int BASE = 13;
const int MOD = 1e8+7;
bool played[MOD];

int coverhash(string s) {
    int h = 0;
    for (int i = 0; i < s.size(); ++i)
        h = (h * BASE %MOD + s[i]-'.') %MOD;
    return h;
}
string moving(vector<int> cell, string mask, II d) {
    map<int, int> check;
    for (int pos: cell) {
        II u = {pos/m, pos%m};
        II v = {u.fi + d.fi, u.se + d.se};
        int p = v.fi*m + v.se;
        if (mask[p] == '.') mask[p] = mask[pos];
        check[p] = 1;
    }
    for (int pos: cell)
        if (!check[pos])
            mask[pos] = '.';
    return mask;
}
bool inside(II p) {
    return (0 <= p.fi && p.fi < n && 0 <= p.se && p.se < m);
}
bool canmove(vector<int> cell, string mask, II d) {
    for (int pos: cell) {
        II u = {pos/m, pos%m};
        II v = {u.fi + d.fi, u.se + d.se};
        if (!inside(v))
            return 0;
        int p = v.fi*m + v.se;
        if (!(0 <= p && p < mask.size() && 
            (mask[p] == mask[pos] || mask[p] == '.')))
            return 0;
    }
    return 1;
}
vector<int> bfs(string mask, int pos) {
    vector<int> res; res.push_back(pos);
    int visited[mask.size()] = {}; visited[pos] = 1;
    queue<int> q; q.push(pos);
    char c = mask[pos];

    while (!q.empty()) {
        int pu = q.front(); q.pop();
        II u = {pu/m, pu%m};
        for (int i = 0; i < 4; ++i) {
            II v = {u.fi + dxy[i].fi, u.se + dxy[i].se};
            int pv = v.fi*m + v.se;
            if (0 <= pv && pv < mask.size() && mask[pv] == c && !visited[pv]) {
                res.push_back(pv);
                q.push(pv);
                visited[pv] = 1;
            }
        }
    }
    return res;
}
void print(string s) {
    cout << '\n';
    int p = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << s[++p];
        cout << '\n';
    }
    cout << '\n';
}
bool finished(string mask) {
    for (int i: {13, 14, 17, 18})
        if (mask[i] != '0')
            return 0;
    return 1;
}
void backtrack(string mask, string move) { // DFS
    if (move.size()/2 > 1000)
        return;
    int h = coverhash(mask);
    if (played[h])
        return;
    played[h] = 1;

    // cout << move.size()/2 << ":";
    // print(mask);

    if (finished(mask)) {
        cout << move.size()/2 << '\n';
        for (int i = 0; i < move.size(); ++i) {
            cout << move[i] << ' ';
            if (i & 1) cout << '\n';
        }
        exit(0);
    }
    map<int, int> moved;
    for (int i = 0; i < mask.size(); ++i)
        if (mask[i] != '.' && !moved[mask[i]]) {
            vector<int> cell = bfs(mask, i);
            // for (int i: cell) cout << i << ' '; cout << '\n'; 
            for (int j = 0; j < 4; ++j) {
                if (canmove(cell, mask, dxy[j])) {
                    // print(moving(cell, mask, dxy[j]));
                    backtrack(moving(cell, mask, dxy[j]),
                            move + mask[i] + hxy[j]);
                }
            }
            moved[mask[i]] = 1;
        }
}

void backtrack2(string mask, string move) { // BFS
    queue<pair<string, string>> que;
    que.push({mask, move});

    int step = 0; int highest = 1;
    while (!que.empty()) {
        mask = que.front().fi;
        move = que.front().se;
        que.pop();
        if (move.size() < que.front().se.size())
            cout << ++step << ' ' << que.size() << endl;

        if (finished(mask)) {
            cout << move.size()/2 << '\n';
            for (int i = 0; i < move.size(); ++i) {
                cout << move[i] << ' ';
                if (i & 1) cout << '\n';
            }
            _time();
            exit(0);
        }
        int moved[10] = {};
        for (int i = 0; i < mask.size(); ++i)
            if (mask[i] != '.' && !moved[mask[i]-48]) {
                vector<int> cell = bfs(mask, i);
                
                // for (int i: cell) cout << i << ' '; cout << '\n'; 
                for (int j = 0; j < 4; ++j) {
                    if (canmove(cell, mask, dxy[j])) {
            
            if (mask[i] == '0') {
                if (cell[0] > highest) {
                    highest = cell[0];
                    print(mask);
                    cout << move << '\n';
                }
            }
                        // print(moving(cell, mask, dxy[j]));
                        string newmask = moving(cell, mask, dxy[j]);
                        int h = coverhash(newmask);
                        if (played[h]) continue;
                        que.push({newmask, move + mask[i] + hxy[j]});
                        played[h] = 1;
                    }
                }
                moved[mask[i]-48] = 1;
            }
    }
}

bool solve() {
    cin >> n >> m;
    string mask = "";
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        mask += s;
    }
    backtrack2(mask, "");
    return 0;
}
signed main() {
    fast();
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; ++i) {
        // cout << "Case " << i << ": ";
        if (solve()) {
            cout << "[Test case : " << i << "]";
            break;
        }
        cout << '\n';
        //string s; getline(cin, s);
    }
    //system("pause");
    return _time(), 0;
}                                                                                                                                                                                                                                                                                                               //Created by CUBERLONG
/*
*/