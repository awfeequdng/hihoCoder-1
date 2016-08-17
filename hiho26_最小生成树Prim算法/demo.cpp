#include <iostream>
#define N 1010

using namespace std;
int len[N][N];
int ans = 999999;

int main()
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            cin >> len[i][j];
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        int res = 0;
        int cnt = n-1;
        for(int k = 1; k < n; ++k)
        {
            int index = 0;
            int min = 99999;
            for(int j = 1; j <= n; ++j)
            {
                if(j == i)
                    continue;
                if(len[i][j] < min)
                {
                    min = len[i][j];
                    index = j;
                }
            }
            for(int j = 1; j <= n; ++j)
                if(len[i][j] >  len[i][index] + len[index][j])
                    len[i][j] = len[i][index] + len[index][j];
            res += min;
            len[i][index] = 99999;
        }
        if(ans > res)
            ans = res;
    }
        cout << ans << endl;
    return 0;
}
