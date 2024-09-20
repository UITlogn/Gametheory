#include <bits/stdc++.h>
using namespace std;
int s[100][100];

void print()
{
    for (int i=0; i<9; i++) 
    {
        for (int j=0; j<9; j++) cout<<s[i][j]<<' ';
        cout<<endl;
    }
}

bool kiemtra(int x, int y, int k)
{
    for (int i=0; i<9; i++) if (s[x][i]==k) return false;
    for (int i=0; i<9; i++) if (s[i][y]==k) return false;
    
    int a=x/3, b=y/3;
    for(int i=3*a; i<3*a+3; i++)
        for(int j=3*b; j<3*b+3; j++)
            if(s[i][j]==k) return false;
            
    return true;
}

void sudoku(int x, int y)
{
    if (y==9)
    {
        if(x==8) { print(); exit(0); } 
        else sudoku(x+1,0);
    } 
    else if (s[x][y]==0)
    {
        for (int k=1; k<=9; k++)
        {
            if (kiemtra(x,y,k))
            {
                s[x][y]=k;
                sudoku(x,y+1);
                s[x][y]=0;
            }
        }
    }
    else sudoku(x,y+1);
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    freopen("SUDOKU.inp", "r", stdin);
    freopen("SUDOKU.out", "w", stdout);
    for (int i=0; i<9; i++) 
        for (int j=0; j<9; j++) 
            cin>>s[i][j];
    sudoku(0,0);
    cout<<'"'<<-1<<'"';
    return 0;
}