#include <bits/stdc++.h>
using namespace std;
#define int long long

int dx[] = {0, 1, -1, 0};
int dy[] = {1, 0, 0, -1};

int n;
bool n4;
struct mask {
    int x, y;
    int a[4][4];
};
mask msk;
struct query {
    int x, y, u, v;
};
bool operator < (mask k, mask m) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (k.a[i][j] != m.a[i][j])
                return (k.a[i][j] < m.a[i][j]);
    return 0;
}
map<mask, int> dp;
map<mask, int> dpm;
mask win;

bool inside(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < n;
}
bool solved(mask a) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (a.a[i][j] != win.a[i][j])
                return 0;
    return 1;
}
vector<query> ans;
void trace(mask msk) {
    int i = dp[msk];
    while (i != -1) {
        ans.push_back({msk.x - dx[i], msk.y - dy[i], msk.x, msk.y});
        swap(msk.a[msk.x][msk.y], msk.a[msk.x - dx[i]][msk.y - dy[i]]);
        msk.x -= dx[i];
        msk.y -= dy[i];
        i = dp[msk];
    }
    if (!n4) {
        cout << ans.size() << '\n';
        for (int i = ans.size()-1; i >= 0; --i)
            cout << ans[i].x+1 << ' ' << ans[i].y+1 << ' '
                << ans[i].u+1 << ' ' << ans[i].v+1 << '\n';
        exit(0);
    }
}
void bfs(mask msk) {
    dp[msk] = -1;

    queue<mask> q;
    q.push(msk);
    while (!q.empty()) {
        mask u = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
            mask v = u;
            v.x += dx[i];
            v.y += dy[i];
            if (inside(v.x, v.y)) {
                swap(v.a[u.x][u.y], v.a[v.x][v.y]);
                if (!dp.count(v)) {
                    dp[v] = i;
                    if (solved(v)) {
                        trace(v);
                        return;
                    }
                    q.push(v);
                }
            }
        }
    }
}

vector<query> ansmove;
void move(int x, int y, int u, int v) {
    swap(msk.a[x][y], msk.a[u][v]);
    if (msk.a[x][y] == 16) msk.x = x, msk.y = y;
    else msk.x = u, msk.y = v;
    ansmove.push_back({x, y, u, v});
}
void tracemove(mask msk) {
    vector<query> ans;
    int i = dpm[msk];
    while (i != -1) {
        ans.push_back({msk.x - dx[i], msk.y - dy[i], msk.x, msk.y});
        swap(msk.a[msk.x][msk.y], msk.a[msk.x - dx[i]][msk.y - dy[i]]);
        msk.x -= dx[i];
        msk.y -= dy[i];
        i = dpm[msk];
    }
    for (int i = ans.size()-1; i >= 0; --i)
        move(ans[i].x, ans[i].y, ans[i].u, ans[i].v);
}
void moveto(int x, int y, int val, vector<int> ex) {
    if (msk.a[x][y] == val)
        return;
    dpm[msk] = -1;

    queue<mask> q;
    q.push(msk);
    while (!q.empty()) {
        mask u = q.front(); q.pop();

        for (int i = 0; i < 4; ++i) {
            mask v = u;
            v.x += dx[i];
            v.y += dy[i];
            if (inside(v.x, v.y)) {
                bool checkex = 0;
                for (int i: ex) if (v.a[v.x][v.y] == i) {
                    checkex = 1; break;
                }
                if (checkex) continue;

                swap(v.a[u.x][u.y], v.a[v.x][v.y]);
                if (!dpm.count(v)) {
                    dpm[v] = i;
                    if (u.x == x && u.y == y && v.a[x][y] == val) {
                        tracemove(v);
                        return;
                    }
                    q.push(v);
                }
            }
        }
    }
    return;
}
void move1() {
    moveto(0, 0, 1, vector<int>());
    return;
}
void move2() {
    moveto(0, 1, 2, {1});
    return;
}
void move34() {
    if (msk.a[0][2] == 3 && msk.a[0][3] == 4)
        return;
    moveto(0, 2, 4, {1, 2});
    if (msk.a[0][3] == 3) {
        move(1, 2, 0, 2);
        move(0, 2, 0, 3);
        move(0, 3, 1, 3);
        move(1, 3, 1, 2);
        move(1, 2, 2, 2);
        move(2, 2, 2, 3);
        move(2, 3, 1, 3);
        move(1, 3, 0, 3);
        move(0, 3, 0, 2);
        move(0, 2, 1, 2);
        move(1, 2, 1, 3);
        move(1, 3, 2, 3);
        move(2, 3, 2, 2);
        move(2, 2, 1, 2);
        move(1, 2, 0, 2);
        move(0, 2, 0, 3);
        move(0, 3, 1, 3);
        return;
    }
    moveto(1, 2, 3, {1, 2, 4});

    if (msk.x <= 1 && msk.y < 3)
        move(msk.x, msk.y, msk.x+1, msk.y);
    while (msk.y < 3)
        move(msk.x, msk.y, msk.x, msk.y+1);
    while (msk.x > 0)
        move(msk.x, msk.y, msk.x-1, msk.y);
    move(0, 3, 0, 2);
    move(0, 2, 1, 2);
    return;
}
void move5() {
    moveto(1, 0, 5, {1, 2, 3, 4});
    return;
}
void move913() {
    if (msk.a[2][0] == 9 && msk.a[3][0] == 13)
        return;
    moveto(2, 0, 13, {1, 2, 3, 4, 5});
    if (msk.a[3][0] == 9) {
        move(2, 1, 2, 0);
        move(2, 0, 3, 0);
        move(3, 0, 3, 1);
        move(3, 1, 3, 2);
        move(3, 2, 2, 2);
        move(2, 2, 2, 1);
        move(2, 1, 3, 1);
        move(3, 1, 3, 0);
        move(3, 0, 2, 0);
        move(2, 0, 2, 1);
        move(2, 1, 2, 2);
        move(2, 2, 3, 2);
        move(3, 2, 3, 1);
        move(3, 1, 2, 1);
        move(2, 1, 2, 0);
        move(2, 0, 3, 0);
        move(3, 0, 3, 1);
        return;
    }
    moveto(2, 1, 9, {1, 2, 3, 4, 5, 13});
    if (msk.x == 1 && msk.y == 1)
        move(1, 1, 1, 2);
    while (msk.x < 3)
        move(msk.x, msk.y, msk.x+1, msk.y);
    while (msk.y > 0)
        move(msk.x, msk.y, msk.x, msk.y-1);
    move(3, 0, 2, 0);
    move(2, 0, 2, 1);
    return;
}
void printmsk() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j)
            cout << msk.a[i][j] << ' ';
        cout << '\n';
    }
    cout << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("PZZ.inp", "r", stdin);
    freopen("PZZ.out", "w", stdout);

    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> msk.a[i][j];
            if (msk.a[i][j] == n*n) {
                msk.x = i;
                msk.y = j;
            }
            win.a[i][j] = i*n + j + 1;
        }

    if (n <= 3) {
        bfs(msk);
        return 0;
    }

    move1();
    // cout << "1: " << ansmove.size() << "\n";
    // printmsk();

    move2();
    // cout << "2: " << ansmove.size() << "\n";
    // printmsk();

    move34();
    // cout << "34: " << ansmove.size() << "\n";
    // printmsk();

    move5();
    // cout << "5: " << ansmove.size() << "\n";
    // printmsk();

    move913();
    // cout << "913: " << ansmove.size() << "\n";
    // printmsk();

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            win.a[i][j] = (i+1)*n + (j+1) + 1;
            msk.a[i][j] = msk.a[i+1][j+1];
            if (msk.a[i][j] == 16) {
                msk.x = i;
                msk.y = j;
            }
        }
    n4 = 1;
    n = 3;
    bfs(msk);

    cout << ansmove.size() + ans.size() << '\n';
    for (query i: ansmove)
        cout << i.x+1 << ' ' << i.y+1 << ' '
            << i.u+1 << ' ' << i.v+1 << '\n';
    // cout << '\n';
    for (int i = ans.size()-1; i >= 0; --i)
        cout << ans[i].x+2 << ' ' << ans[i].y+2 << ' '
            << ans[i].u+2 << ' ' << ans[i].v+2 << '\n';
    
    return 0;
}