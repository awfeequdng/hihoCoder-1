#include <iostream>
#include <algorithm>
#define N 10010
using namespace std;

int main()
{
    int n, m;
    int res, oper, a, b, k;
    int weight[N][15];

    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> weight[i][0];
    }

    k = log2(n);

    for(int j = 1; j <= k; ++j)
    {
        for(int i = 1; i + (1<<j) - 1 <= n; ++i)
        {
            weight[i][j] = min(weight[i][j-1], weight[i + (1<<(j-1))][j-1]);
        }
    }

    cin >> m;
    while(m--)
    {
        cin >> oper >> a >> b;
        if(oper == 0)
        {
            k = log2(b - a + 1);
            cout << min(weight[a][k], weight[b - (1<<k) + 1][k]) << endl;
        }
        else
        {
            weight[a][0] = b;

            for(int j = 1; j <= log2(n); ++j)
            {
                for(int i = a; a - i < (1<<j) && i > 0; --i)
                {
                    if(i + (1<<j) - 1 <= n)
                        weight[i][j] = min(b, weight[i][j]);
                    else
                        continue;
                }
            }
        }
    }
    return 0;
}
