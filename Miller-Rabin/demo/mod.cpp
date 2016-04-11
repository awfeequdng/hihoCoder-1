//求(x*y)%n
#include <iostream>
using namespace std;
typedef long long llong;
llong mod(llong x, llong y, llong n)
{
    llong ret = 0;
    llong temp = x % n;
    while(y)
    {
        if(y & 0x1)
            if((ret += temp) > n)
                ret -= n;
        if((temp <<= 1) >  n)
            temp -= n;
        y >>= 1;
    }
    return ret;
}
int main()
{
    llong a, b, c;
    while(cin >> a >> b >> c)
        cout << "the result is: " << mod(a, b, c) << endl;
    return 0;
}
/*
llong mod(llong x, llong y, llong n)
{
    llong ret = 0;
    llong temp = x % n;
    while(y)
    {
        if(y & 0x1)
            if((ret += temp) > n)
                ret -= n;
        if((temp <<= 1) > n)
            temp -= n;
        y >>= 1;
    }
    return ret;
}*/
