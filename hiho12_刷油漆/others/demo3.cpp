#include <stdio.h>
#include <string.h>
#define MAXL 204
//#define LL 201
#define LL 102
int to[MAXL],next[MAXL],last[MAXL];
int cnt;
int used[LL],value[LL];
int dp[LL][LL];
int n,m;
void init()
{
	memset(to,0,sizeof(to));
	memset(next,0,sizeof(next));
	memset(last,0,sizeof(last));
	memset(used,0,sizeof(used));
	memset(value,0,sizeof(value));
	return ;
}
void add_node(int x,int y)
{
	to[cnt]=y;
	next[cnt]=last[x];
	last[x]=cnt;
	cnt++;
	return;
}
void  find_max(int x)
{
	int i;
	used[x]=1;
	for (i=last[x];i>0;i=next[i])
	{
		int y=to[i];
        if (!used[y])
        {
		find_max(y);
		int j,k;
		for (j=m;j>=2;j--)
		{
			for (k=1;k<j;k++)
			{
				if (dp[x][j]<dp[y][k]+dp[x][j-k])
					dp[x][j]=dp[y][k]+dp[x][j-k];
			}
		}
        }
	}
	return;
}
int main()
{
	scanf("%d%d",&n,&m);
	cnt=1;
	int i;
	init();
	for (i=1;i<=n;i++)
		scanf("%d",&value[i]);
	for (i=0;i<n-1;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add_node(x,y);
		add_node(y,x);
	}
	for (i=1;i<=n;i++)
		dp[i][1]=value[i];
	find_max(1);
	printf("%d\n",dp[1][m]);
}
