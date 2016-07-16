#include<cstdio>
#include<cstring>
const int mod = 1000000007;
int dp[1010][1<<5], up[1<<5];
int n, m, f[]={3,6,12,24,15,27,30};
void add(int &x, int v){
    x += v;
    while(x>=mod)  x-=mod;
}
int main(){
    int L = 7;
    scanf("%d%d",&n,&m);
    if((n*m)&1){
        puts("0");
        return 0;
    }
    m = 1<<m;
    memset(dp,0,sizeof(dp));
    memset(up,0,sizeof(up));
    dp[0][m-1]=1;
    for(int k=1; k<=n; k++)
    {
        for(int j=0; j<m; j++)
        {
            add(dp[k][j], dp[k-1][(m-1)^j]);
            for(int i=0; i<L; i++)i
            {
                if(f[i]>=m || (j&f[i]))
                    continue;
                add(up[j|f[i]], dp[k][j]);
            }
        }
        for(int j=0; j<m; j++)
        {
            add(dp[k][j], up[j]);
            up[j]=0;
        }
    }
    printf("%d\n", dp[n][m-1]);
    return 0;
}
