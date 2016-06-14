#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int i,j,k,m,n,t;
int a[105][105];

int l[10005],r[10005],d[10005],u[10005],h[10005],s[10005];
int noden,lien;
void init()
{
   memset(l,0,sizeof(l));
   memset(r,0,sizeof(r));
   memset(u,0,sizeof(u));
   memset(d,0,sizeof(d));
   memset(h,0,sizeof(h));
   memset(s,0,sizeof(s));
   lien=m;noden=m;
   for (i=0;i<=lien;i++)
   {
      l[i]=i-1;r[i]=i+1;
      u[i]=i;d[i]=i;
      s[i]=0;h[i]=i;
   }
   l[0]=lien;r[lien]=0;
}
void insert(int hang)
{
   int i,j,k,first=0;
   for (i=1;i<=m;i++)
   {
      if (a[hang][i]==1)
      {
         noden++;
         if (first==0) first=noden;
         l[noden]=noden-1;r[noden]=noden+1;
         d[noden]=i;u[noden]=u[i];
         d[u[i]]=noden;u[i]=noden;
         h[noden]=i;s[i]++;
      }
   }
   l[first]=noden;
   r[noden]=first;
}
void remove(int lienum)
{
   int i,j,k;
   r[l[lienum]]=r[lienum];l[r[lienum]]=l[lienum];
   for (i=d[lienum];i!=lienum;i=d[i])
   {
      for (j=r[i];j!=i;j=r[j])
      {
         u[d[j]]=u[j];d[u[j]]=d[j];
         s[h[j]]--;
      }
   }
}
void restore(int lienum)
{
   int i,j,k;
   r[l[lienum]]=lienum;l[r[lienum]]=lienum;
   for (i=u[lienum];i!=lienum;i=u[i])
   {
      for (j=l[i];j!=i;j=l[j])
      {
         u[d[j]]=j;d[u[j]]=j;
         s[h[j]]++;
      }
   }
}
bool dfs()
{
   int i,j,k=r[0];
   if (r[0]==0) return true;
   for (i=r[0];i!=0;i=r[i]) if (s[i]<s[k]) k=i;
   remove(k);
   for (i=d[k];i!=k;i=d[i])
   {
      for (j=r[i];j!=i;j=r[j]) remove(h[j]);
      if (dfs()) return true;
      for (j=l[i];j!=i;j=l[j]) restore(h[j]);
   }
   restore(k);
   return false;
}
int main()
{
   scanf("%d",&t);
   for (;t>=1;t--)
   {
      scanf("%d%d",&n,&m);
      for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%d",&a[i][j]);
      init();
      for (i=1;i<=n;i++) insert(i);
      if (dfs()) printf("Yes\n");else printf("No\n");
   }
   //pause("pause");
   return 0;
}
