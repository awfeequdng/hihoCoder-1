#include <iostream>
#include <string.h>
#define N 1005

using namespace std;

int main()
{
    unsigned len[N][N];
    memset(len, -1, sizeof(len));
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    int from, to;
    unsigned length;
    for(int i = 0; i < m; ++i)
    {
        cin >> from >> to >> length;
        length = min(length, len[from][to]);
        len[from][to] = len[to][from] = length;
    }

    int index;
    int value;
    while(1)
    {
        index = 1;
        value = len[s][1];
        for(int i = 2; i <= n; ++i)
        {
            if(value > len[s][i])
            {
                value = len[s][i];
                index = i;
            }
        }

        for(int i = 1; i <= n; ++i)
        {
            if(len[index][i] != (unsigned)-1)
            {
                len[s][i] = min(len[s][index] + len[index][i], len[s][i]);
            }
        }

        if(index == t)
        {
            break;
        }
        else
        {
            len[s][index] = -1;
        }
    }
    cout << len[s][t] << endl;
    return 0;
}
