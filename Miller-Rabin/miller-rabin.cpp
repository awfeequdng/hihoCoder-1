#include <iostream>
#include <cstdlib>
using namespace std;
typedef long long llong;
//求取(x * y) % n
llong mod(llong x, llong y,llong n)
{
    llong res = 0;
    llong temp = x % n;
    while(y)
    {
        if(y & 0x1)
            if((res += temp) > n)
                res -= n;
        if((temp <<= 1) >  n)
            temp -= n;
        y >>= 1;
    }
    return res;
}

//求取(x ^ y) % n
llong get_mod(llong x, llong y, llong n)
{
    llong res = 1;
    llong temp = x;
    while(y)
    {
        if(y & 0x1)
            res = mod(res, temp, n);
        temp = mod(temp, temp, n);
        y >>= 1;
    }
    return res;
}

//编写bool函数，判定是否为素数
bool is_prime(llong n, int t)
{
    if(n < 2)
        return false;
    if(n == 2)
        return true;
    if(!(n & 0x1))
        return false;
    llong k = 0, m, a, i;
    for(m = n -1; !(m & 0x1); m >>= 1, ++k);
    while(t--)
    {
        a = get_mod(rand() % (n - 2) + 2, m, n);
        if(a != 1)
        {
            for(i = 0; i < k && a != n-1; ++i)
            {
                a = mod(a, a, n);
            }
            //根据二次探测定理，只要不满足(a == 1) || (a == n - 1)，就会一直遍历下去，直到最后返回false
            if(i >= k)
                return false;
        }
    }
    return true;
}

//主函数
int main()
{
    int times;
    llong num;
    cin >> times;
    while(times--)
    {
        cin >> num;
        if(is_prime(num, 1))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
