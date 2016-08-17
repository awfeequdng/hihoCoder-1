#include <iostream>  
#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <algorithm>  
using namespace std;  
struct Node  
{  
    int u;  
    int v;  
    int cost;  
}e[1000006];  
  
int fa[100005];  
bool com(Node p,Node q)     //升序排序   
{  
    return p.cost < q.cost;  
}  
int find(int x)       //并查集   
{  
    if(x == fa[x])  
    {  
        return x;  
    }  
    return fa[x] = find(fa[x]);  
}  
int main()  
{  
    int n,m;  
    cin>>n>>m;  
    for(int i = 0;i < m;i++)  
    {  
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].cost);  
    }  
      
    sort(e,e + m,com);            //排序   
    for(int i = 1;i <= n;i++)  
    {  
        fa[i] = i;  
    }  
      
    int k = 0;  
    int res = 0;  
    int x,y;  
    int cnt = 0;  
    for(int i = 1;i < n;i++)       //找n-1条边   
    {  
        for(int j = k;j < m;j++)  //找最小边   
        {  
            x = find(e[j].u);       
            y = find(e[j].v);
            cout << x << " " << y << endl;  
            if(x == y)           //属于同一个集合   
            {  
                continue;  
            }  
            fa[x] = y;          // 加入同一个集合   
            res += e[j].cost;   
            k = j + 1;  
            break;             //找到了一条   
        }
    }  
    printf("%d\n",res);  
    return 0;  
}