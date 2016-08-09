#include <iostream>
using namespace std;

int main()
{
    int price[100010];
    int n, m;
    int oper, l, r, d;
    int sum = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= n; ++i)
    {
        scanf("%d", &price[i]);
        sum += price[i];
    }
    while(m--)
    {
        scanf("%d%d%d%d", &oper, &l, &r, &d);
        if(oper == 0)
        {
            sum += (r - l + 1) * d;
            while(l <= r)
            {
                price[l] += d;
                l++;
            }
        }
        else
        {
            while(l <= r)
            {
                sum += d - price[l];
                price[l] = d;
                l++;
            }
        }
        printf("%d\n", sum);
    }
    return 0;
}
