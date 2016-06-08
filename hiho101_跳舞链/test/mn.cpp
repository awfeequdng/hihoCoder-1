#include <iostream>
using namespace std;
int m, n;

void print()
{
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cout << mn[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int temp;
    cin >> m >> n;
    static int num[m][n];
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cin >> temp;
            num[i][j] = temp;
        }
    }
    print();
    return 0;
}
