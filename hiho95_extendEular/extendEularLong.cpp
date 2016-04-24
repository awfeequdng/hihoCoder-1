#include <iostream>
typedef long long llong;
using namespace std;
int gcd(llong a, llong b)
{
    if(a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

pair<llong, llong> extend_gcd(llong a, llong b)
{
    if(gcd(a, b) == b)
        return make_pair(0, 1);
    pair<llong, llong> p = extend_gcd(b, a % b);
    pair<llong, llong> res;
    res.first = p.second;
    res.second = p.first - (a / b) * p.second;
    return res;
}
llong solve(llong s1, llong s2, llong v1, llong v2, llong m)
{
    llong a = v1 - v2;
    llong b = m;
    llong c = s2 - s1;
    if(a < 0)
        a = a + m;
    llong d = gcd(a, b);
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
    llong s1, s2, v1, v2, m;
    cin >> s1 >> s2 >> v1 >> v2 >> m;
    cout << solve(s1+1, s2+1, v1, v2, m) << endl;
    return 0;
}
