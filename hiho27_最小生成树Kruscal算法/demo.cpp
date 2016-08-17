#include <iostream>
#define N 100010
#define M 1000010
using namespace std;
typedef struct node
{
    int from, to, value;
}*Node;

node len[M];
int rep[N];
bool visit[M] = {false};

//并查集的核心代码
int findRep(int n)
{
    if(rep[n] == n)
        return n;
    else
    {
        rep[n] = findRep(rep[n]);
        return rep[n];
    }
}

int main()
{
    int n, m;
    int res = 0;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
    {
        rep[i] = i;
    }
    int from, to, value;
    for(int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d", &from, &to, &value);
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
        }
        from = len[index].from;
        to = len[index].to;
        visit[index] = true;
        if(from)
            rep[to] = findRep(from);
        else
            rep[from] = findRep(to);
        for(int i = 1; i <= n; ++i)
            cout << rep[i] << " ";
        cout << endl;
        res += min;
    }
    printf("%d\n", res);
    return 0;
}
