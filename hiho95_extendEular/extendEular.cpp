#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    if(a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

pair<int, int> extend_gcd(int a, int b)
{
    if(a % b)
        return make_pair(0, 1);
    pair<int, int> p = extend_gcd(b, a % b);
    pair<int, int> res;
    res.first = p.second;
    res.second = p.first - (a / b) * p.second;
    return res;
}
int main()
{
    int a, b;
    while(cin >> a >> b)
    {
        cout << gcd(a, b) << endl;
    }
    return 0;
}
