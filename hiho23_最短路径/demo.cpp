#include <iostream>
#include <string.h>
#define N 1005
using namespace std;

unsigned len[N][N];

int main()
{
    int n, m, s, t;
    int from, to;
    unsigned length;
    memset(len, -1, sizeof(len));
    scanf("%d%d%d%d", &n, &m, &s, &t);
    //cin >> n >> m >> s >> t;
    for(int i = 0; i < m; ++i)
    {
        scanf("%d%d%u", &from, &to, &length);
        //cin >> from >> to >> length;
        length = min(len[from][to], length);
        len[from][to] = len[to][from] = length;
    }
    int min_id;
    unsigned min_val;
    while(1)
    {
        min_id = 1;
        min_val = len[s][1];
        for(int i = 2; i <= n; ++i)
        {
            if(len[s][i] < min_val)
            {
                min_val = len[s][i];
                min_id = i;
            }
        }

        for(int i = 1; i <= n; ++i)
        {
            if(len[min_id][i] != (unsigned)-1)
            {
                len[s][t] = min(len[s][min_id] + len[min_id][i], len[s][i]);
            }
        }

        if(min_id == t)
        {
            cout << len[s][t] << endl;
            break;
        }
        else
        {
            len[s][min_id] = -1;
        }
    }
    return 0;
}
