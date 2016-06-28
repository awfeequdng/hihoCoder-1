#include<cstdio>
#include<iostream>
#include <cstdlib>

using namespace std;

int n,root,i,tot,opt,x;
int father[100000],count[100000],data[100000],value[100000];
int son[100000][3];

inline void Rotate(int x,int w)
{
	int y;
	y=father[x];
	count[y]=count[y]-count[x]+count[son[x][w]];
	count[x]=count[x]-count[son[x][w]]+count[y];
	son[y][3-w]=son[x][w];
	if (son[x][w]) father[son[x][w]]=y;
	father[x]=father[y];
	if (father[y])
		if (y==son[father[y]][1]) son[father[y]][1]=x;
			else son[father[y]][2]=x;
	father[y]=x;
	son[x][w]=y;
}

inline void splay(int x)
{
	int y;
	while (father[x])
	{
		y=father[x];
		if (!father[y])
			if (x==son[y][1]) Rotate(x,2);
			else Rotate(x,1);
		else
			if (y==son[father[y]][1])
				if (x==son[y][1])
				{
					Rotate(y,2);Rotate(x,2);
				}
				else
				{
					Rotate(x,1);Rotate(x,2);
				}
				else
				if (x==son[y][2])
				{
					Rotate(y,1);Rotate(x,1);
				}
				else
				{
					Rotate(x,2);Rotate(x,1);
				}
	}
	root=x;
}

inline int search(int x,int w)
{
	while (data[x]!=w)
	{
		if (w==data[x]) return x;
		if (w<data[x])
		{
			if (!son[x][1]) break;
			x=son[x][1];
		}
		else
		{
			if (son[x][2]==0) break;
			x=son[x][2];
		}
	}
	return x;
}

inline void insert(int w)
{
	int k,kk;bool flag;
	if (!tot)
	{
		tot=1;
		father[1]=0;count[1]=1;data[1]=w;root=1;value[1]=1;
		return;
	}
	k=search(root,w);
	if (data[k]==w)
	{
		value[k]++;kk=k;
		flag=true;
	}
	else
	{
		tot++;
		data[tot]=w;
		father[tot]=k;
		count[tot]=1;
		value[tot]=1;
		if (data[k]>w) son[k][1]=tot;else son[k][2]=tot;
		flag=0;
	}
	while (k)
	{
		count[k]++;
		k=father[k];
	}
	if (flag) splay(kk);else splay(tot);
}

inline int Extreme(int x,int w)
{
	const int lala[3]={0,2147483647,-2147483647};
	int k,tmp;
	k=search(x,lala[w]);
	tmp=data[k];
	splay(k);
	return tmp;
}

inline void del(int x)
{
	int k,y;
	k=search(root,x);
	if (data[k]!=x) splay(k);else
	{
		splay(k);
		if (value[k]>1)
		{
			value[k]--;
			count[k]--;
		}
		else
		if (!son[k][1])
		{
			y=son[k][2];
			son[k][2]=0;
			count[k]=0;
			data[k]=0;
			value[k]=0;
			root=y;
			father[root]=0;
		}
		else
		{
			father[son[k][1]]=0;
			y=Extreme(son[k][1],1);
			son[root][2]=son[k][2];
			count[root]=count[root]+count[son[k][2]];
			if (son[root][2]!=0) father[son[root][2]]=root;
				data[k]=0;son[k][1];son[k][2]=0;
				value[k]=0;
		}
	}
}

inline int pred(int x)
{
	int k;
	k=search(root,x);
	splay(k);
	if (data[k]<x) return data[k];
	return Extreme(son[k][1],1);
}

inline int succ(int x)
{
	int k;
	k=search(root,x);
	splay(k);
	if (data[k]>x) return data[k];
	return Extreme(son[k][2],2);

}

inline int kth(int x,int w)
{
	int i,tmp;
	i=root;
	while (!((x>=count[son[i][w]]+1)&&(x<=count[son[i][w]]+value[i]))&&(i!=0))
	{
		if (x>count[son[i][w]]+value[i])
		{
			x=x-count[son[i][w]]-value[i];
			i=son[i][3-w];
		}
		else
		i=son[i][w];
	}
	tmp=i;
	splay(i);
	return tmp;
}

inline int findnum(int x)
{
	int k;
	k=search(root,x);splay(k);
	root=k;
	return count[son[k][1]]+1;
}

int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		if (i==3)
		i=3;
		scanf("%d%d",&opt,&x);
		switch(opt)
		{
			case 1:insert(x);break;
			case 2:del(x);break;
			case 3:printf("%d\n",findnum(x));break;
			case 4:printf("%d\n",data[kth(x,1)]);break;
			case 5:printf("%d\n",pred(x));break;
			case 6:printf("%d\n",succ(x));break;
			default:break;
		}
	}
	return 0;
}