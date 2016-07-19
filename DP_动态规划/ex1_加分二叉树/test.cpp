#include <iostream>
using namespace std;
int score[100];
int root[100][100];
int dp[100][100];
int n;

void DP()
{
    for(int i = 1; i <= n; ++i)
    {
        dp[i][i] = score[i];
        root[i][i] = i;
    }
    for(int i = 1; i < n; ++i)
    {
        dp[i][i+1] = score[i] + score[i+1];
        root[i][i+1] = i;
    }
    for(int d = 2; d < n; ++d)
    {
        for(int i = 1; i <= n-d; ++i)
        {
            int temp;
            dp[i][i+d] = dp[i][i] + dp[i+1][i+d];
            root[i][i+d] = i;
            for(int j = i+1; j < i+d; ++j)
            {
                temp = dp[i][j-1] * dp[j+1][i+d] + dp[j][j];
                if(temp > dp[i][i+d])
                {
                    dp[i][i+d] = temp;
                    root[i][i+d] = j;
                }
            }
            if(dp[i][i+d-1] + dp[i+d][i+d] > temp)
            {
                dp[i][i+d] = dp[i][i+d-1] + dp[i+d][i+d];
                root[i][i+d] = i+d;
            }
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> score[i];
    }
    DP();
    cout << dp[1][n] << endl;
}
