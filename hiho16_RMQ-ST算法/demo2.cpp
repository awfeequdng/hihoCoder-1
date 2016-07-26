#include <iostream>
#include <algorithm>
using namespace std;
#define N 1000010

int dp[N][20];

int main()
{
    int n, m, next;
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> dp[i][0];

    int k = log2(n);
    for(int j = 1; j <= k; ++j)
    {
        for(int i = 0; i+(1<<j)-1 < n; ++i)
        {
            next = i + (1<<(j-1));
            dp[i][j] = min(dp[i][j-1], dp[next][j-1]);
        }
    }
    /*
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= k; ++j)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/

    cin >> m;
    int l, r;
    while(m--)
    {
        cin >> l >> r;
        l--;
        r--;
        k = log2(r - l + 1);
        cout << min(dp[l][k], dp[r - (1<<k) + 1][k]) << endl;
    }
    return 0;
}
