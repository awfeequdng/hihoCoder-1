#include <iostream>
#include <string.h>
#define N 100010
using namespace std;

unsigned len[N][N] = {-1};

int main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    int from, to;
    unsigned length;
    for(int i = 1; i <= m; ++i)
    {
        cin >> from >> to >> length;
        len[from][to] = len[to][from] = min(len[from][to], length);
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
