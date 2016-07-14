#include <iostream>
#include <memory.h>

using namespace std;

const int b[6]={1, 2, 4, 8, 16, 32};

int n, m;
bool can[32][32];
int f[1001][32];

bool check(int x, int y)
{
     bool last=false;
     for (int k=0; k<m; ++k)
     {
         if (x&b[k])
            {if (last || (y&b[k])) return false;}
         else if ((y&b[k])&& last) return false;
         if ((y&b[k])==0) if (x&b[k]) last=false; else last=!last;
     }
     return !last;
}

int main()
{
    cin >> n >> m;
    for (int i=0; i<b[m]; ++i)
        for (int j=0; j<b[m]; ++j)
            can[i][j]=check(i, j);
    memset(f, 0, sizeof f);
    f[0][0]=1;
    for (int i=1; i<=n; ++i)
        for (int j=0; j<b[m]; ++j)
            for (int k=0; k<b[m]; ++k)
                if (can[j][k]) f[i][k]=(f[i][k]+f[i-1][j])%1000000007;
    cout << f[n][0] << endl;
}
