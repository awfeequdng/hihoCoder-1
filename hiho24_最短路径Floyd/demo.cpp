#include <iostream>
#include <string.h>
#define N 105
using namespace std;

unsigned len[N][N];

int main()
{
    int n, m;
    int from, to;
    unsigned length;
    memset(len, -1, sizeof(len));
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        len[i][i] = 0;
    for(int i = 1; i <= m; ++i)
    {
        cin >> from >> to >> length;
        len[from][to] = len[to][from] = min(length, len[from][to]);
    }
    for(int k = 1; k <= n; ++k)
    {
        for(int i = 1; i <= n; ++i)
        {
            for(int j = 1; j <= n; ++j)
            {
                if(len[i][k] != (unsigned)-1 && len[k][j] != (unsigned)-1)
                {
                    len[i][j] = len[j][i] = min(len[i][j], len[i][k] + len[k][j]);
                }
            }
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            cout << len[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
