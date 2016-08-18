#include <iostream>  
#include <cstdio>  
#include <cstring>  
using namespace std;  
int q[100005];  
void HeapAdjust(int loc,int len)  
{  
    int pos=loc,leftchild=2*loc,rightchild=2*loc+1;  
    if(loc<=len/2)  
    {  
        if(leftchild<=len&&q[leftchild]>q[pos])  
            pos=leftchild;  
        if(rightchild<=len&&q[rightchild]>q[pos])  
            pos=rightchild;  
        if(pos!=loc)  
        {  
            swap(q[pos],q[loc]);  
            HeapAdjust(pos,len);  
        }  
    }  
    return;  
}  
int main()  
{  
    int n,len=0,b;  
    char a;  
    scanf("%d",&n);  
    getchar();  
    for(int j=1;j<=n;j++)  
    {  
        cin>>a;  
        if(a=='A')  
        {  
            scanf("%d",&q[++len]);  
            int l=len/2;  
            while(l!=0)                 //依次往上维护堆    
            {  
                HeapAdjust(l,len);  
                l=l/2;  
            }  
            getchar();  
        }  
        else if(a=='T')  
        {  
            printf("%d\n",q[1]);  
            swap(q[1],q[len--]);  
            HeapAdjust(1,len);          //维护  
        }  
    }  
    return 0;  
} 