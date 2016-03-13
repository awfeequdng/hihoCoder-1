#include <iostream>
using namespace std;
int count(int a)
{
    int temp = 0;
    for(int i = 1; i <= a; ++i)
    {
        if(a % i == 0)
            temp++;
    }
    return temp;
}
int main()
{
    int n;
    while(cin >> n)
    {
        int temp = 0;
        int res = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(count(i) > temp)
            {
                temp = count(i);
                res = i;
            }
        }
        cout << res << endl;
    }
    return 0;
}
