#include <iostream>
#define N 1005
using namespace std;

int main()
{
    int n;
    int res = 0;
    cin >> n;
    int len[N][N];
    int value[N];
    bool visit[N] = {false};
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            cin >> len[i][j];
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        value[i] = len[1][i];
    }
    int k = n-1;
    visit[1] = true;
    while(k--)
    {
        int index = 0;
        int min = 99999;
        for(int i = 2; i <= n; ++i)
        {
            if(!visit[i] && value[i] < min)
            {
                min = value[i];
                index = i;
            }
        }
        visit[index] = true;
        res += min;
        for(int i = 1; i <= n; ++i)
        {
            if(!visit[i] && len[index][i] < value[i])
            {
                value[i] = len[index][i];
            }
        }
    }
    cout << res << endl;
    return 0;
}
