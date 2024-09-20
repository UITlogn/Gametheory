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
// ví trí góc trên trái của các loại block
// 0: 0: 2x2
// 1: 1, 2, 3, 4: 2x1 (cao 2 rộng 1)
// 2: 5: 1x2 (cao 1 rộng 2)
// 3: 6, 7, 8, 9: 1x1
// 4: ô trống

bool operator==(II u, II v) {
	return u.fi == v.fi && u.se == v.se;
}
bool operator!=(II u, II v) {
	return u.fi != v.fi || u.se != v.se;
}
struct Mask {
	II a0;
	II a1[4];
	II a2;
	II a3[4];
	II a4[2];
	void print() {
		char a[5][4];
		a[a0.fi][a0.se] = a[a0.fi][a0.se+1] = 
		a[a0.fi+1][a0.se] = a[a0.fi+1][a0.se+1] = '0';

		for (int i = 0; i < 4; ++i)
			a[a1[i].fi][a1[i].se] =
			a[a1[i].fi+1][a1[i].se] = '1';
		
		a[a2.fi][a2.se] = '2';
		a[a2.fi][a2.se+1] = '2';

		for (int i = 0; i < 4; ++i)
			a[a3[i].fi][a3[i].se] = '3';
		
		for (int i = 0; i < 2; ++i)
			a[a4[i].fi][a4[i].se] = ' ';
		
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 4; ++j) cout << a[i][j];
			cout << '\n';
		}
	}
	bool emp(II s) {
		for (int i = 0; i < 2; ++i)
			if (s.fi == a4[i].fi && s.se == a4[i].se)
				return 1;
		return 0;
	}
	Mask() {
		a0 = {0, 1};

		a1[0] = {0, 0}; a1[1] = {0, 3};
		a1[2] = {2, 0}; a1[3] = {2, 3};

		a2 = {2, 1};

		a3[0] = {3, 1}; a3[1] = {3, 2};
		a3[2] = {4, 0}; a3[3] = {4, 3};

		a4[0] = {4, 1}; a4[1] = {4, 2};
	}
	bool check_win() {
		return (a0.fi == 3 && a0.se == 1);
	}
	bool operator == (Mask m) {
		if (a0 != m.a0) return 0;
		for (int i = 0; i < 4; ++i)
			if (a1[i] != m.a1[i]) return 0;
		if (a2 != m.a2) return 0;
		for (int i = 0; i < 4; ++i)
			if (a3[i] != m.a3[i]) return 0;
		return 1;
	}
};
string tostr(II s) {
	return to_string(s.fi) + ',' + to_string(s.se);
}
vector<Mask> played;
bool check_played(Mask mask) {
	for (Mask m: played)
		if (m == mask)
			return 1;
	return 0;
}
void backtrack(Mask mask, string move) {
	if (check_played(mask))
		return;
	played.push_back(mask);
	
	mask.print(); cout << '\n';
	if (mask.check_win()) {
		cout << move;
		exit(0);
	}
	// block 2x2 (0) move:
	if (mask.emp({mask.a0.fi-1, mask.a0.se}) && 
		mask.emp({mask.a0.fi-1, mask.a0.se+1})) {// up
			Mask newmsk = mask;
			newmsk.a4[0].fi += 2;
			newmsk.a4[1].fi += 2;
			--newmsk.a0.fi;
			backtrack(newmsk, move + tostr(mask.a0) + " U\n");
		}
	if (mask.emp({mask.a0.fi+2, mask.a0.se}) && 
		mask.emp({mask.a0.fi+2, mask.a0.se-1})) {// down
			Mask newmsk = mask;
			newmsk.a4[0].fi -= 2;
			newmsk.a4[1].fi -= 2;
			++newmsk.a0.fi;
			backtrack(newmsk, move + tostr(mask.a0) + " D\n");
		}
	if (mask.emp({mask.a0.fi, mask.a0.se-1}) && 
		mask.emp({mask.a0.fi+1, mask.a0.se-1})) {// left
			Mask newmsk = mask;
			newmsk.a4[0].se += 2;
			newmsk.a4[1].se += 2;
			--newmsk.a0.se;
			backtrack(newmsk, move + tostr(mask.a0) + " L\n");
		}
	if (mask.emp({mask.a0.fi, mask.a0.se+2}) && 
		mask.emp({mask.a0.fi+1, mask.a0.se+2})) {// right
			Mask newmsk = mask;
			newmsk.a4[0].se -= 2;
			newmsk.a4[1].se -= 2;
			++newmsk.a0.se;
			backtrack(newmsk, move + tostr(mask.a0) + " R\n");
		}

	// block 2x1 move
	for (int i = 0; i < 4; ++i) {
		if (mask.emp({mask.a1[i].fi-1, mask.a1[i].se})) {// up
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a1[i].fi-1, mask.a1[i].se))
				newmsk.a4[0].fi += 2;
			else newmsk.a4[1].fi += 2;
			--newmsk.a1[i].fi;
			backtrack(newmsk, move + tostr(mask.a1[i]) + " U\n");
		}
		if (mask.emp({mask.a1[i].fi+2, mask.a1[i].se})) {// down
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a1[i].fi+2, mask.a1[i].se))
				newmsk.a4[0].fi -= 2;
			else newmsk.a4[1].fi -= 2;
			++newmsk.a1[i].fi;
			backtrack(newmsk, move + tostr(mask.a1[i]) + " D\n");
		}
		if (mask.emp({mask.a1[i].fi, mask.a1[i].se-1}) && 
			mask.emp({mask.a1[i].fi+1, mask.a1[i].se-1})) {// left
				Mask newmsk = mask;
				++newmsk.a4[0].se, ++newmsk.a4[1].se;
				--newmsk.a1[i].se;
				backtrack(newmsk, move + tostr(mask.a1[i]) + " L\n");
			}
		if (mask.emp({mask.a1[i].fi, mask.a1[i].se+1}) && 
			mask.emp({mask.a1[i].fi+1, mask.a1[i].se+1})) {// right
				Mask newmsk = mask;
				--newmsk.a4[0].se, --newmsk.a4[1].se;
				++newmsk.a1[i].se;
				backtrack(newmsk, move + tostr(mask.a1[i]) + " R\n");
			}
	}

	// block 1x2 move
	if (mask.emp({mask.a2.fi-1, mask.a2.se}) && 
		mask.emp({mask.a2.fi-1, mask.a2.se+1})) {// up
			Mask newmsk = mask;
			++newmsk.a4[0].fi, ++newmsk.a4[1].fi;
			--newmsk.a2.fi;
			backtrack(newmsk, move + tostr(mask.a2) + " U\n");
		}
	if (mask.emp({mask.a2.fi+1, mask.a2.se}) && 
		mask.emp({mask.a2.fi+1, mask.a2.se-1})) {// down
			Mask newmsk = mask;
			--newmsk.a4[0].fi, --newmsk.a4[1].fi;
			++newmsk.a2.fi;
			backtrack(newmsk, move + tostr(mask.a2) + " D\n");
		}
	if (mask.emp({mask.a2.fi, mask.a2.se-1})) {// left
		Mask newmsk = mask;
		if (newmsk.a4[0] == make_pair(mask.a2.fi, mask.a2.se-1))
			newmsk.a4[0].se += 2;
		else newmsk.a4[1].se += 2;
		--newmsk.a2.se;
		backtrack(newmsk, move + tostr(mask.a2) + " L\n");
	}
	if (mask.emp({mask.a2.fi, mask.a2.se+2})) {// right
		Mask newmsk = mask;
		if (newmsk.a4[0] == make_pair(mask.a2.fi, mask.a2.se+2))
			newmsk.a4[0].se -= 2;
		else newmsk.a4[1].se -= 2;
		++newmsk.a2.se;
		backtrack(newmsk, move + tostr(mask.a2) + " R\n");
	}

	// block 1x1 move
	for (int i = 0; i < 4; ++i) {
		if (mask.emp({mask.a3[i].fi-1, mask.a3[i].se})) {// up
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a2.fi, mask.a2.se+2))
				++newmsk.a4[0].fi;
			else ++newmsk.a4[1].fi;
			--newmsk.a3[i].fi;
			backtrack(newmsk, move + tostr(mask.a3[i]) + " U\n");
		}
		if (mask.emp({mask.a3[i].fi+1, mask.a3[i].se})) {// down
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a3[i].fi+1, mask.a3[i].se))
				--newmsk.a4[0].fi;
			else --newmsk.a4[1].fi;
			++newmsk.a3[i].fi;
			backtrack(newmsk, move + tostr(mask.a3[i]) + " D\n");
		}
		if (mask.emp({mask.a3[i].fi, mask.a3[i].se-1})) {// left
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a3[i].fi, mask.a3[i].se-1))
				++newmsk.a4[0].se;
			else ++newmsk.a4[1].se;
			--newmsk.a3[i].se;
			backtrack(newmsk, move + tostr(mask.a3[i]) + " L\n");
		}
		if (mask.emp({mask.a3[i].fi, mask.a3[i].se+1})) {// right
			Mask newmsk = mask;
			if (newmsk.a4[0] == make_pair(mask.a3[i].fi, mask.a3[i].se+1))
				--newmsk.a4[0].se;
			else --newmsk.a4[1].se;
			++newmsk.a3[i].se;
			backtrack(newmsk, move + tostr(mask.a3[i]) + " R\n");
		}
	}
}
bool solve() {
	Mask a;
	backtrack(a, "");
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