#include <iostream>
using namespace std;
int ref[] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
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
    int n, m, q, temp;
    cin >> n >> m >> q;
    int state = 0;
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        cin >> temp;
        state = (((state << 1) + 1) & ref[m]);
        if(count(state) <= q)
            res += temp;
        else
            state -= 1;
    }
    cout << res << endl;
    return 0;
}
