#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=100000+1;
const int MAXM=1000000+1;
int N,M,S,T,head[MAXN],queue[MAXM],front=0,rear=0,e=0;
int ans[MAXN];
struct EDGE
{
    int v,next,cost;
}edge[MAXM<<1];

void addEdge(int x,int y,int z)
{
    edge[e].v=y;
    edge[e].cost=z;
    edge[e].next=head[x];
    head[x]=e++;
}

void bfs(int x)
{
    queue[rear++]=x;
    while(front<rear)
    {
        x=queue[front++];
        for(int p=head[x];p!=-1;p=edge[p].next)
        if(ans[edge[p].v]==-1 || ans[x]+edge[p].cost<ans[edge[p].v])
        {
            ans[edge[p].v]=ans[x]+edge[p].cost;
            queue[rear++]=edge[p].v;
        }
    }
}

int main()
{
    memset(head,-1,sizeof(head));
    memset(ans,-1,sizeof(ans));
    scanf("%d%d%d%d",&N,&M,&S,&T);

    int a,b,c;
    while(M--)
    {
        scanf("%d%d%d",&a,&b,&c);
        addEdge(a,b,c);
        addEdge(b,a,c);
    }

    ans[S]=0;
    bfs(S);

    printf("%d",ans[T]);

    return 0;
}