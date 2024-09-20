#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define int long long
#define ld long double

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
long long Rand(long long l, long long h) { 
    // sinh số ngẫu nhiên trong -1e18 <= l <= Rand(l,r) <= r <= 1e18
    if (l >= h) return l;
    long long range = (h - l + 1);
    long long ans = rd()%10;
    while (ans < 1e18) {
        ans = ans*10 + rd()%10;
        if (ans < 0) ans = -ans;
    }
    return l + ans % range;
}
bool bit01() { // tra ve 0 hoac 1
    return Rand(1, 1e5)%2;
}
char az() { // tra ve ki tu ngau nhien tong ['a' .. 'z']
    return (char)(Rand('a', 'z'));
}
char AZ() { // tra ve ki tu ngau nhien tong ['A' .. 'Z']
    return (char)(Rand('A', 'Z'));
}
char num() { // tra ve ['0' .. '9']
    return '0' + Rand(0, 9);
}
void ShuffleArray(vector<int> &arr, int n) {
	int minPosition;
	int maxPosition = n - 1;
	int swapPosition;
	int i = 0;
	while (i < n - 1) {
		minPosition = i + 1;
		swapPosition = Rand(1, 1e7) % (maxPosition - minPosition + 1) + minPosition;
		swap(arr[i], arr[swapPosition]);
		++i;
	}
}
signed main() {
    string NAME = "POW";

    HANDLE cons;
    cons = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(cons, 15);
    cout << "Creating " << NAME << ".exe" << endl;
    system(("g++ -g " + NAME + ".cpp -o " + NAME + ".exe").c_str());
    cout << "Creating ___TRAU___.exe" << endl;
    system("g++ -g ___TRAU___.cpp -o ___TRAU___.exe");
    cout << endl;

    for (int iTest = 1; iTest <= 17; iTest++) {
        ofstream out(NAME + ".inp");
        cout << "Test " << iTest << ": ";
        //vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv<<<<<<

            out << iTest;


        //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^<<<<<<
        out.close();
        ifstream checkempty(NAME + ".inp");
        if (checkempty.peek() == std::ifstream::traits_type::eof()) {
            cout << "___EMPTY INPUT___";
            break;
        }
        int time_begin = clock();
        if (system((NAME + ".exe").c_str()) != 0) {
            SetConsoleTextAttribute(cons, 96);
            cout << " RTE ";
            SetConsoleTextAttribute(cons, 15);
            system("pause");
            continue;
        }
        int time_end = clock();
        system("___TRAU___.exe");
        int time_trau = clock();
        cout << time_end-time_begin << "ms";

        if (time_end-time_begin > 1e50) {
            SetConsoleTextAttribute(cons, 112);
            cout << " TLE ";
            SetConsoleTextAttribute(cons, 15);
            system("pause");
        }
        cout << ", " << time_trau-time_end << "ms: ";
        
        SetConsoleTextAttribute(cons, 15);
        if (system(("fc " + NAME + ".out ___TRAU___.out").c_str()) != 0) {
            SetConsoleTextAttribute(cons, 64);
            cout << " WRONG " << endl;
            SetConsoleTextAttribute(cons, 15);
            system("pause");
        } else {
            SetConsoleTextAttribute(cons, 160);
            cout << " ACCEPTED " << endl;
            SetConsoleTextAttribute(cons, 15);
        }
    }
    system("pause");
    return 0;
}