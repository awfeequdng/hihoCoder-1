#include <iostream>
using namespace std;
int m, n;

void print(int num[m][n])
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cout << num[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int temp;
    cin >> m >> n;
    int num[m][n];
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cin >> temp;
            num[i][j] = temp;
        }
    }
    print(num);
    return 0;
}
