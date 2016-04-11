#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace std;
int get_mod(int a, int b, int c)
{
    long long res = 1;
    long long temp = a;
    while(b > 0)
    {
        if( b & 0x1)
        {
            res = (res * temp) % c;
        }
        temp = (temp * temp) % c;
        b >>= 1;
    }
    return static_cast<int> (res);
}
bool Miller_Rabin(int n)
{
    if (n < 2)
        return false;
    if(n == 2 || n == 3)
        return true;

    for(int i = 0; i < 25; ++i)
    {
        int a = rand() % (n - 1) + 1;
        int y = get_mod(a, n-1, n);
        if(y != 1)
            return false;
        long long u = n - 1;
        while(u % 2 == 0 && u > 1)
        {
            int x = get_mod(a, u, n);
            if(x != 1 && x != n-1)
                return false;
            u = u / 2;
        }
    }
    return true;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    int temp;
    while(n--)
    {
        cin >> temp;
        nums.push_back(temp);
    }
    for(const auto num : nums)
    {
        if(Miller_Rabin(num))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    for(int i=0; i < 1000; ++i)
    {
        if(Miller_Rabin(i))
            cout << i << " ";
    }
    cout << endl;
    return 0;
}
    /*
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace std;
int get_mod(int a, int b, int c)
{
    long long res = 1;
    long long temp = a;
    while(b > 0)
    {
        if( b & 1)
        {
            res = (res * temp) % c;
        }
        temp = (temp * temp) % c;
        b >>= 1;
    }
    return static_cast<int> (res);
}
bool Miller_Rabin(int n)
{
    if (n < 2) 
        return false;
    if(n == 2 || n == 3)
        return true;

    long long u = n - 1;
    while(u % 2 == 0)
        u = u / 2;
    for(int i = 0; i < 5; ++i)
    {
        int a = rand() % (n - 2) + 2;
        int y = get_mod(a, n-1, n);
        if(y != 1)
            return false;
        int x = get_mod(a, u, n);
        if(x == 1 || x == n-1)
            continue;
        for(int i = u; i < n; i *= 2)
        {
            x = x * x % n;
            if(x == 1)
                return false;
            if(x == n-1)
            {
                break;
                continue;
            }
            return false;

        }
    }
    return true;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    int temp;
    while(n--)
    {
        cin >> temp;
        nums.push_back(temp);
    }
    for(const auto num : nums)
    {
        if(Miller_Rabin(num))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    for(int i=0; i < 1000; ++i)
    {
        if(Miller_Rabin(i))
            cout << i << " ";
    }
    cout << endl;
    return 0;
}
*/
/*#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace std;
typedef long long  llong;
llong get_mod(llong a, llong b, llong c)
{
    llong res = 1;
    while(b--)
        res = res * a % c;
    return res;
}
bool Miller_Rabin(llong n)
{
    if(n < 2)
        return false;
    if(n ==2 || n == 3)
        return true;
    auto u = n - 1;
    for(int i = 0; i < 5;  ++i)
    {
        llong a = rand() % (n-3) + 2;
        if(get_mod(a, u, n) != 1)
            return false;
    } 
    return true;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    int temp;
    while(n--)
    {
        cin >> temp;
        nums.push_back(temp);
    }
    for(const auto num : nums)
    {
        if(Miller_Rabin(num))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}*/

/*
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace std;
int get_mod(int a, int b, int c)
{
    long long res = 1;
    long long temp = a;
    while(b > 0)
    {
        if( b & 1)
        {
            res = (res * temp) % c;
        }
        temp = (temp * temp) % c;
        b >>= 1;
    }
    return static_cast<int> (res);
}
bool Miller_Rabin(int n)
{
    if (n < 2) 
        return false;
    if(n == 2 || n == 3)
        return true;

    long long u = n - 1;
    while(u % 2 == 0)
        u = u / 2;
    for(int i = 0; i < 5; ++i)
    {
        int a = rand() % (n - 2) + 2;
        int x = get_mod(a, u, n);
        while(u < n)
        {
            auto y = x * x % n;
            if(y == 1 && x != 1 && x != n-1)
                return false;
            x = y;
            u = u * 2;
        }
        if(x != 1)
            return false;
    }
    return true;
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums;
    int temp;
    while(n--)
    {
        cin >> temp;
        nums.push_back(temp);
    }
    for(const auto num : nums)
    {
        if(Miller_Rabin(num))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}*/
