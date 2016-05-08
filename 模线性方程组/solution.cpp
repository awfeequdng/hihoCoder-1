#include <iostream>
#include <vector>
typedef long  llong;
using namespace std;
long gcd(llong a, llong b)
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

int main()
{
    long num;
    cin >> num;
    vector<long> m;
    vector<long> r;
    long a, b;
    for(int i = 0; i < num; ++i)
    {
        cin >> a >> b;
        m.push_back(a);
        r.push_back(b);
    }
    auto M = m[0];
    auto R = r[0];
    for(int i = 1; i < num; ++i)
    {
        auto d = gcd(M, m[i]);
        auto c = r[i] - R;
        if(c % d)
            return -1;
        auto k = extend_gcd(M / d, m[i] / d);
        k.first = (c / d * k.first) % (m[i] / d);
        R = R + k.first * M;
        M = M / d * m[i];
        R %= M;
    }
    if(R < 0)
        R =  R + M;
    cout << R << endl;
    return 0;
}
