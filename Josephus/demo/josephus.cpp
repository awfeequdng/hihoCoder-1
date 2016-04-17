#include <iostream>
using namespace std;
int main()
{
    int num, n, k;
    cin >> num;
    while(num--)
    {
        int ret = 0;
        cin >> n >> k;
        for(int i = 2; i <= n; ++i)
        {
            ret = (ret + k) % i;
        }
        cout << ret << endl;
    }
    return 0;
}
