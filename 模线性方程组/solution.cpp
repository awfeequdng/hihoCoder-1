#include <iostream>
#include <vector>
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

int main()
{
    int num;
    cin >> num;
    vector<int> m;
    vector<int> r;
    int a, b;
    for(int i = 0; i < num; ++i)
    {
        cin >> a >> b;
        m.push_back(a);
        r.push_back(r);
    }
    int M = m[0];
    int R = r[0];
    for(int i = 1; i < num; ++i)
    {
        auto d = gcd(M, m[i]);
        auto c = r[i] - R;
        if(c mod d)
            return -1;
        auto k = extend_gcd(M / d, m[i] / d);
        k.first = (c / d * k.first) mod (m[i] / d);
        R = R + k.first * M;
        M = M / d * m[1];
        R %= M;
    }
    if(R < 0)
        R =  R + M;
    cout << R << endl;
    return 0;
}