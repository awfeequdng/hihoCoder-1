#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

const int MAX = 100005;
int dis[MAX], vis[MAX] ,head[MAX];
int n, m, s, t, cnt;

struct edge
{
    int v, w, next;
}edge[1000005];

void addedge(int u, int v, int w)
{
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void spfa(int s)
{
    int pos, v;
    queue<int> q;
    q.push(s);
    dis[s] = 0; vis[s] = 1;
    while(!q.empty())
    {
        pos = q.front(); q.pop();
        vis[pos] = 0;
        for(int i = head[pos]; i != -1; i = edge[i].next)
        {
            v = edge[i].v;
            if(dis[pos] + edge[i].w < dis[v])
            {
                dis[v] = dis[pos] + edge[i].w;
                if(!vis[v])
                {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }
    }
}

int main() 
{
    while(scanf("%d %d %d %d", &n, &m, &s, &t) != EOF)
    {
        cnt = 0;
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        memset(dis, 0x37, sizeof(dis));
        while(m--)
        {
            int x, y, w;
            scanf("%d %d %d", &x, &y, &w);
            addedge(x, y, w);
            addedge(y, x, w);
        }
        spfa(s);
        printf("%d\n", dis[t]);
    }
    return 0;
}