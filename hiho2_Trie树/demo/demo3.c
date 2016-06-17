#include<stdio.h>
#include<stdlib.h>
struct data{
    int next[26];
    int cnt;
}f[10000000];
int tot=0;
char s[20];
void insert()
{
    int now=0;
    char *p=s;
    while (*p)
    {
        int idx=(int)(*p-'a');
        if (!f[now].next[idx])
        {
            tot++;
            f[now].next[idx]=tot;
        }
        now=f[now].next[idx];
        f[now].cnt++;
        p++;
    }
}
void print()
{
    int now=0;
    char *p=s;
    while (*p)
    {
        int idx=(int)(*p-'a');
        if (!f[now].next[idx])
        {
            printf("0\n");
            return ;
        }
        now=f[now].next[idx];
        p++;
    }
    printf("%d\n",f[now].cnt);
}
int main()
{
    int n,m,i;
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        scanf("%s",s);
        insert();
    }
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        scanf("%s",s);
        print();
    }
}
