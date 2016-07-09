#include <iostream>

using namespace std;

int num[100][100];

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            cin >> num[i][j];
            cout << num[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
