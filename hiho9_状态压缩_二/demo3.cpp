#include <iostream>
#define  M (1<<m)-1
using namespace std;

int k[] = {3, 6, 12, 24, 15, 27, 30};
int res[1000][32] = {1};
int o = 1e9 + 7;

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        //横着填放
        for(int j = M; j >= 0; --j)
        {
            for(int t = 0; t < 7; ++t)
            {
                if((j&(k[t])) == k[t])
                {
                    res[i][j] += res[i][j&~k[t]];
                    res[i][j] %= o;
                }
            }
        }
        //竖着填放
        for(int j = 0; j <= M; ++j)
        {
            res[i+1][M&~j] += res[i][j];
            res[i+1][m&~j] %= o;
        }
    }
    cout << res[n-1][M] << endl;
}
