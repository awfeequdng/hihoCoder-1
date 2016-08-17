#include <iostream>
#define N 1005
using namespace std;

int main()
{
    int n;
    int len[N][N];
    int temp[N][N];
    int pre[N] = {1};
    int res = 0;
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            cin >> len[i][j];
            temp[i][j] = len[i][j];
        }
    }
    for(int j = 1; j < n; ++j)
    {
        int index = 2;
        int min = len[1][2];
        for(int i = 2; i <= n; ++i)
        {
            if(min > len[1][i])
            {
                min = len[1][i];
                index = i;
            }
        }
        for(int i = 1; i <= n; ++i)
        {
            if(len[1][i] > len[1][index] + len[index][i])
            {
                len[1][i] = len[1][index] + len[index][i];
                pre[i] = index;
            }
        }
        res += temp[pre[index]][index];
        len[1][index] = 99999;
    }
    cout << res << endl;
    return 0;
}
