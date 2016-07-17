#include <iostream>
#include <memory.h>
#include <algorithm>
#define NMax 1000
#define MMax (1<<5)

using namespace std;

bool testFistLine(int s, int m)
{
    int i = 0;
    while(i < m)
    {
        if((s&(1<<i)) == 0)
            i++;
        else if(i == m-1 || !(s & (1<<(i+1))))
            return false;
        else
            i += 2;
    }
    return true;
}

bool testCompatible(int sa, int sb, int m)
{
    int i = 0;
    while(i < m)
    {
        if((sa & (1<<i)) == 0)
        {
            if((sb & (1<<i)) == 0)
                return false;
            ++i;
        }
        else
        {
            if((sb & (1<<i)) == 0)
                ++i;
            else if(i == m-1 || !((sa & (1<<(i+1))) && (sb & (1<<(i+1)))))
                return false;
            else
                i += 2;
        }
    }
    return true;
}

int main()
{
    int n;
    int m;
    cin >> n >> m;
    int res[NMax][MMax];
    int allState = 1<<m;
    memset(res, 0, sizeof(res));

    for(int s = 0; s < allState; ++s)
        if(testFistLine(s, m))
            res[0][s] = 1;

    for(int i = 1; i < n; ++i)
    {
        for(int j = 0; j < allState; ++j)
        {
            for(int k = 0; k < allState; ++k)
            {
                if(testCompatible(j, k, m))
                {
                    res[i][j] += res[i-1][k];
                    res[i][j] %= 1000000007;
                }
            }
        }
    }
    cout << res[n-1][allState - 1] << endl;
    return 0;
}
