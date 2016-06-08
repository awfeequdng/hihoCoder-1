#include <iostream>
#include <stack>
using namespace std;

int main()
{
    int t;
    int temp;
    int n, m;
    cin >> t;
    while(t--)
    {
        cin >> n >> m;
        int num[n][m];
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                cin >> temp;
                num[i][j] = temp;
                cout << num[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
