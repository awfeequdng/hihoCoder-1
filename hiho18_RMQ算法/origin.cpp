#include <iostream>
#define N 10010
using namespace std;
int main()
{
    int n, m;
    int oper, res, a, b;
    int node[N];
    cin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cin >> node[i];
    }

    cin >> m;
    while(m--)
    {
        cin >> oper >> a >> b;
        if(oper == 1)
        {
            node[a] = b;
        }
        else
        {
            res = node[a];
            for(int i = a; i <= b; ++i)
            {
                if(node[i] < res)
                    res = node[i];
            }
            cout << res << endl;
        }
    }
    return 0;
}
