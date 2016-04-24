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
int solve(int s1, int s2, int v1, int v2, int m)
{
    int a = v1 - v2;
    int b = m;
    int c = s2 - s1;
    if(a < 0)
        a = a + m;
    int d = gcd(a, b);
    if(c % d)
        return -1;
    a = a / d;
    b = b / d;
    c = c / d;
    auto res = extend_gcd(a, b);
    res.first = (res.first * c) % b;
    while(res.first < 0)
        res.first += b;
    return res.first;
}

int main()
{
    int s1, s2, v1, v2, m;
    cin >> s1 >> s2 >> v1 >> v2 >> m;
    cout << solve(s1, s2, v1, v2, m) << endl;
    return 0;
}
