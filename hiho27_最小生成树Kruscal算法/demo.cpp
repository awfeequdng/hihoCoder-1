#include <iostream>
#define N 100010
using namespace std;
typedef struct node
{
    int from, to, value;
}*Node;

node len[N];
int rep[N];
bool visit[N] = {false};

int findRep(int n)
{
    if(rep[n] == n)
        return n;
    else
    {
        rep[n] = findRep(n);
        return rep[n];
    }
}

int main()
{
    int n, m;
    int res = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
    {
        rep[i] = i;
    }
    int from, to, value;
    for(int i = 1; i <= m; ++i)
    {
        cin >> from >> to >> value;
        len[i].from = from;
        len[i].to = to;
        len[i].value = value;
    }
    int k = n-1;
    while(k--)
    {
        int index = 0;
        int min = 999999;
        int from, to;
        for(int i = 1; i <= m; ++i)
        {
            if(visit[i])
                continue;
            from = len[i].from;
            to = len[i].to;
            value = len[i].value;
            if(rep[from] == rep[to])
            {
                visit[i] = true;
                continue;
            }
            else
            {
                if(min > value)
                {
                    min = value;
                    index = i;
                }
            }
            //cout << k << " " << min << " " << len[i].value << endl;
        }
        from = len[index].from;
        to = len[index].to;
        rep[from] = findRep(to);
        cout << from << "->" << to << endl;
        for(int i = 1; i <= n; ++i)
            cout << rep[i] << " ";
        cout << endl;
        visit[index] = true;
        res += min;
    }
    cout << res << endl;
    return 0;
}
