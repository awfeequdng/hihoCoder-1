#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
    int from, to, value;
}path[1000010];

int rep[100010];

int findRep(int n)
{
    if(rep[n] == n)
        return n;
    return rep[n] = findRep(rep[n]);
}

bool com(node a, node b)
{
    return a.value < b.value;
}

int main()
{
    int n, m;
    int res = 0;
    int k = 1;
    cin >> n >> m;
    for(int i = 1; i <= m; ++i)
    {
        cin >> path[i].from >> path[i].to >> path[i].value;
    }
    for(int i = 1; i <= n; ++i)
        rep[i] = i;

    sort(path, path+m, com);

    for(int i = 1; i < n; ++i)
    {
        for(int j = k; j <= m; ++j)
        {
            int a = findRep(path[j].from);
            int b = findRep(path[j].to);
            if(a == b)
                continue;
            /*if(a == path[j].from)
                rep[path[j].to] = a;
            else
                rep[path[j].from] = b;*/
            rep[a] = b;

            res += path[j].value;
            k = j + 1;
            break;
        }
    }
    cout << res << endl;
    return 0;
}
