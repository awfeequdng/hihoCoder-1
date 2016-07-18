#include <cstdio>
int max(int a,int b){return a<b?b:a;}
const int N=105;
int to[N*3],nx[N*3],hd[N],cn=0,dp[N][N],n,m,u,v;
void con(int u,int v){
    to[++cn]=v;
    nx[cn]=hd[u];
    hd[u]=cn;
}
void cl(int u,int p){
    for(int i=hd[u];i;i=nx[i])if(to[i]!=p){
        cl(to[i],u);
        for(int c=m;c>=2;--c)for(int t=1;t<c;++t)dp[u][c]=max(dp[u][c],dp[u][c-t]+dp[to[i]][t]);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&dp[i][1]);
    for(int i=1;i<n;++i){
        scanf("%d%d",&u,&v);
        con(u,v);con(v,u);
    }
    cl(1,-1);
    printf("%d\n",dp[1][m]);
}