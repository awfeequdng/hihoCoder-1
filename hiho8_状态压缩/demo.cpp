#include <iostream>
using namespace std;
int ref[] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
int best[1001];
int count(int n)
{
    int res = 0;
    while(n > 0)
    {
        n = n >> 1;
        res++;
    }
    return res;
}
int main()
{
    for(auto x : best)
        x = 0;
    int n, m, q, temp;
    cin >> n >> m >> q;
    int state = 0;
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> temp;
        if(i == 0)
            best[0] = temp;
        for(int j = 1; j < n; ++j)
        {
            state = (((state <<  1) + 1) & ref[m]);
            if(count(state) <= q)
                best[i] = best[i - 1] + temp;
            else
            {
                state -= 1;
                best[i] = best[i-1];
            }
        }
    }
    for(const auto x : best)
        if(res < x)
            res = x;
    cout << res << endl;
    return 0;
}
