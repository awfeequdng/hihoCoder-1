#include <iostream>
using namespace std;
int b[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
int sum[2][5][1024] = {1};
int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < b[m]; ++j)
        {
            for(int k = 0; k < b[2 * m]; ++k)
            {
            }
        }
    }
    return 0;
}
