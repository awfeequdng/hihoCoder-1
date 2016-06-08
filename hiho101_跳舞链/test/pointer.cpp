#include <iostream>
using namespace std;

int main()
{
    int temp;
    int test[5][5];
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            cin >> temp;
            test[i][j] = temp;
        }
    }
    return 0;
}
