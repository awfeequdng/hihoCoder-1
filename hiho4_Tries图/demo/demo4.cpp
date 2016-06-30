#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
struct Trie{
	bool isdan;
	int link[26];
	int pre;
}T[1000010];
int Count=1;
char s[1000010],p[1000010];
queue<int> q;
void build_trie(int len)
{
	int pos=1;
	for(int i=0;i<len;i++){
		if(T[pos].link[p[i]-'a']==-1){
			T[pos].link[p[i]-'a']=++Count;
			for(int j=0;j<26;j++) T[Count].link[j]=-1;
			T[Count].isdan=false;
		}
		pos=T[pos].link[p[i]-'a'];
		if(i==len-1) T[pos].isdan=true;
	}
}
void build_G()
{
	q.push(1);
	while(!q.empty()){
		int proot=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			int child=T[proot].link[i];
			if(child!=-1){
				int ppre=T[proot].pre;
				while(ppre!=-1){
					if(T[ppre].link[i]!=-1){
						T[child].pre=T[ppre].link[i];
						if(T[T[child].pre].isdan) T[child].isdan=true;
						break;
					}
					else ppre=T[ppre].pre;
				}
				q.push(child);
			}
		}
	}
}
bool solve()
{
	int pos=1;
	for(int i=0;s[i];i++){
		while(true){
			if(T[pos].link[s[i]-'a']!=-1){
				pos=T[pos].link[s[i]-'a'];
				if(T[pos].isdan) return true;
				break;
			}
			else pos=T[pos].pre;
		}
	}
	return false;
}


int main()
{
	int n;
	scanf("%d",&n);


	for(int j=0;j<26;j++) T[1].link[j]=-1;
	for(int i=1;i<=n;i++){
		scanf("%s",p);
		build_trie(strlen(p));
	}

	for(int i=0;i<26;i++) T[0].link[i]=1;
	T[1].pre=0;T[0].pre=-1;T[0].isdan=false;
	build_G();
	


	scanf("%s",s);

	if(solve()) printf("YES\n");
	else printf("NO\n");
	return 0;
}