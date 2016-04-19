#include <iostream>
using namespace std;
int josephus(int n, int k)
{
    int ret;
    if(n == 1)
        return 0;
    if(n < k)
    {
        int ret = 0;
        for(int i = 2; i <= n; ++i)
            ret = (ret + k) % i;
        return ret;
    }
    ret = josephus(n-n/k,k);
    if(ret < n % k)
    {
        ret = ret - n % k + n;
    }
    else
    {
        ret = ret - n % k + (ret - n % k ) / (k - 1);
    }
    return ret;
}
int main()
{
    int num;
    cin >> num;
    while(num--)
    {
        int n, k;
        cin >> n >> k;
        cout << josephus(n, k) << endl;
    }
    return 0;
}
