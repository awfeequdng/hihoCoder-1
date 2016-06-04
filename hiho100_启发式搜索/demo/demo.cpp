//启发式搜索。网上的写法，已经通过，网上写法的判重部分有问题。
#include <stdio.h>  
#include <string.h>  
#include <math.h>  
#include <queue>  
#include <stack>  
#include <algorithm>  
#include <iostream>
using namespace std;  
int Hash[15];    
struct node  
{  
	int f,h,g;  
	int x,y;  
	char map[3][3];  
	friend bool operator< (const node &a,const node &b)  
	{  
		if(a.f==b.f)  
			return a.g<b.g;  
		return a.f>b.f;  
	}  
};  

node start;

int pos[][2]= {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};  
bool vis[500000];   
int to[4][2]={0,-1,0,1,-1,0,1,0};

int check()//判断不可能的状况  
{  
	int i,j,k;  
	int s[20];  
	int cnt = 0;  
	for(i = 0; i<3; i++)  
	{  
		for(j = 0; j<3; j++)  
		{  
			s[3*i+j] = start.map[i][j];  
			if(s[3*i+j] == 'x')  
				continue;  
			for(k = 3*i+j-1; k>=0; k--)  
			{  
				if(s[k] == 'x')  
					continue;  
				if(s[k]>s[3*i+j])  
					cnt++;  
			}  
		}  
	}  
	if(cnt%2)  
		return 0;  
	return 1;  
}  

int solve(node a)//康托  
{  
	int i,j,k;  
	int s[20];  
	int ans = 0;  
	for(i = 0; i<3; i++)  
	{  
		for(j = 0; j<3; j++)  
		{  
			s[3*i+j] = a.map[i][j];  
			int cnt = 0;  
			for(k = 3*i+j-1; k>=0; k--)  
			{  
				if(s[k]>s[3*i+j])  
					cnt++;  
			}  
			ans = ans+Hash[i*3+j]*cnt;  
		}  
	}  
	return ans;  
}  

int get_h(node a)//得到H值  
{  
	int i,j;  
	int ans = 0;  
	for(i = 0; i<3; i++)  
	{  
		for(j = 0; j<3; j++)  
		{  
			if(a.map[i][j] == 'x')  
				continue;  
			int k = a.map[i][j]-'1';  
			ans+=abs(pos[k][0]-i)+abs(pos[k][1]-j);  
		}  
	}  
	return ans;  
}  

int bfs()  
{  
	memset(vis,0,sizeof(vis));  
	priority_queue<node> Q;  
	start.g = 0;  
	start.h = get_h(start);  
	start.f = start.h; 
	vis[solve(start)]=true;
	if(solve(start)==0)  return 0;
	Q.push(start);  
	node next;
	while(!Q.empty())  
	{  
		node a = Q.top();  
		Q.pop();  
		int k_s = solve(a);  
		vis[k_s]=true;
		for(int i = 0; i<4; i++)  
		{  
			next = a;  
			next.x+=to[i][0];  
			next.y+=to[i][1];  
			if(next.x < 0 || next.y < 0 || next.x>2 || next.y > 2)  
				continue;  
			next.map[a.x][a.y] = a.map[next.x][next.y];  
			next.map[next.x][next.y] = 'x';  
			next.g+=1;  
			next.h = get_h(next);  
			next.f = next.g+next.h;  
			int k_n = solve(next);  
			if(vis[k_n])  
				continue;  
			Q.push(next);  
			if(k_n == 0)  
				return next.g;  
		}  
	}  
}  

int main()  
{    
	Hash[0] = 1;  
	for(int i = 1; i<=9; i++)  
		Hash[i] = Hash[i-1]*i;  
	int t=0;
	cin>>t;
	char a=0;
	for (int i=0;i<t;i++)
	{
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				cin>>a;
				start.map[i][j]=a;
				if(a=='0')  
				{
					start.map[i][j]='x';
					start.x=i;
					start.y=j;
				}
			}
		}
		if(!check())  
		{  
			cout<<"No Solution!"<<endl;  
		}  
		else cout<<bfs()<<endl;  
	} 
	return 0;  
}